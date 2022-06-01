// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>

#ifndef INCLUDE_PAGECONTAINER_HPP_
#define INCLUDE_PAGECONTAINER_HPP_

#include <set>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include "Observer.hpp"
#include "StatSender.hpp"
#include "UsedMemory.hpp"
#include "Histogram.hpp"
#include "Log.hpp"

class PageContainer {
 public:
  explicit PageContainer(StatSender* sender = new StatSender,
                         UsedMemory* use_memory = new UsedMemory,
                         Histogram* hist = new Histogram);
  ~PageContainer();
  void push_observer(Observer* observer);

 public:
  void Load(std::istream& io, float threshold);
  const Item& ByIndex(size_t i) const;
  const Item& ById(const std::string& id) const;
  void Reload(float threshold);
  size_t get_size() {
    return (_observers.capacity()+
            _data.capacity() +
            _raw_data.capacity());
  }

 private:
  void LoadRawData(std::istream& io);
  void OnDataLoaded(const std::vector<Item>& new_items);
  void OnRawDataLoaded(const std::vector<std::string>& new_items);
  void OnSkipped(const Item& item);

 private:
  std::vector<Observer*> _observers;
  std::vector<Item> _data;
  std::vector<std::string> _raw_data;
};

#endif  // INCLUDE_PAGECONTAINER_HPP_
