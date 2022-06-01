// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>

#include "UsedMemory.hpp"

UsedMemory::UsedMemory()
    :_used(0){}

void UsedMemory::OnDataLoaded(const std::vector<Item>& old_items,
                              const std::vector<Item>& new_items) {
  Log::get_instance().WriteDebug("UsedMemory::OnDataLoad");
  for (const auto& item : old_items) {
    _used -= item.id.capacity();
    _used -= item.name.capacity();
    _used -= sizeof(item.score);
  }

  for (const auto& item : new_items) {
    _used += item.id.capacity();
    _used += item.name.capacity();
    _used += sizeof(item.score);
  }
  Log::get_instance().Write("UsedMemory::OnDataLoad: new size = " +
                            std::to_string(_used));
}

void UsedMemory::OnRawDataLoaded(const std::vector<std::string>& old_items,
                                 const std::vector<std::string>& new_items) {
  Log::get_instance().WriteDebug("UsedMemory::OnRawDataLoads");
  for (const auto& item : old_items) {
    _used -= item.capacity();
  }

  for (const auto& item : new_items) {
    _used += item.capacity();
  }
  Log::get_instance().Write("UsedMemory::OnDataLoad: new size = " +
                            std::to_string(_used));
}

size_t UsedMemory::used() const { return _used; }
