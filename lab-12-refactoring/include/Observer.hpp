// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>

#ifndef INCLUDE_OBSERVER_HPP_
#define INCLUDE_OBSERVER_HPP_

#include <string>
#include <vector>

struct Item {
  std::string id;
  std::string name;
  float score = 0;
};

class Observer {
 public:
  Observer() = default;
  virtual ~Observer() = default;
  virtual void OnDataLoaded(const std::vector<Item>& old_items,
                            const std::vector<Item>& new_items) = 0;
  virtual void OnRawDataLoaded(const std::vector<std::string>& old_items,
                               const std::vector<std::string>& new_items) = 0;
  virtual void OnSkipped(const Item& item) = 0;
};


#endif // INCLUDE_OBSERVER_HPP_
