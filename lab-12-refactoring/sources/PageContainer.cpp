// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>

#include "PageContainer.hpp"

constexpr size_t kMinLines = 10;

PageContainer::PageContainer(StatSender* sender,
                             UsedMemory* use_memory,
                             Histogram* hist)
{
  push_observer(sender);
  push_observer(use_memory);
  push_observer(hist);
}

PageContainer::~PageContainer() {
  for (auto& observer : _observers) {
    delete observer;
  }
}

void PageContainer::push_observer(Observer* observer) {
  _observers.emplace_back(observer);
}

void PageContainer::Load(std::istream& io, float threshold) {
  LoadRawData(io);
  Reload(threshold);
}

void PageContainer::LoadRawData(std::istream& io) {
  std::vector<std::string> raw_data;

  if (!io) throw std::runtime_error("Can't open file.");

  while (!io.eof()) {
    std::string line;
    std::getline(io, line, '\n');
    raw_data.push_back(std::move(line));
  }

  if (raw_data.size() < kMinLines) {
    throw std::runtime_error("too small input stream");
  }

  OnRawDataLoaded(raw_data);
  _raw_data = std::move(raw_data);
}

const Item& PageContainer::ByIndex(size_t i) const { return _data[i]; }

const Item& PageContainer::ById(const std::string& id) const {
  auto it = std::find_if(std::begin(_data), std::end(_data),
                         [&id](const auto& i) { return id == i.id; });
  return *it;
}

void PageContainer::Reload(float threshold) {
  std::vector<Item> data;
  std::set<std::string> ids;
  for (const auto& line : _raw_data) {
    std::stringstream stream(line);

    Item item;
    stream >> item.id >> item.name >> item.score;

    if (auto&& [_, inserted] = ids.insert(item.id); !inserted) {
      throw std::runtime_error("already seen");
    }

    if (item.score > threshold) {
      data.push_back(std::move(item));
    } else {
      OnSkipped(item);
    }
  }

  if (data.size() < kMinLines) {
    throw std::runtime_error("oops");
  }

  OnDataLoaded(data);
  _data = std::move(data);
}

void PageContainer::OnDataLoaded(const std::vector<Item>& new_items) {
  for (auto& observer : _observers) {
    observer->OnDataLoaded(_data, new_items);
  }
}

void PageContainer::OnRawDataLoaded(const std::vector<std::string>& new_items) {
  for (auto& observer : _observers) {
    observer->OnRawDataLoaded(_raw_data, new_items);
  }
}

void PageContainer::OnSkipped(const Item& item) {
  for (auto& observer : _observers) {
    observer->OnSkipped(item);
  }
}
