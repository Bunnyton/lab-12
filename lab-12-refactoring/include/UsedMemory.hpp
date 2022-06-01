// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>

#ifndef INCLUDE_USEDMEMORY_HPP_
#define INCLUDE_USEDMEMORY_HPP_

#include <vector>
#include <string>

#include "Observer.hpp"
#include "Log.hpp"

class UsedMemory: public Observer {
 public:
  UsedMemory();
  ~UsedMemory() override = default;

 public:
  void OnDataLoaded(const std::vector<Item>& old_items,
                    const std::vector<Item>& new_items) override;
  void OnRawDataLoaded(const std::vector<std::string>& old_items,
                       const std::vector<std::string>& new_items) override;
  void OnSkipped(const Item&) override {}

 public:
  size_t used() const;

 private:
  size_t _used;
};

#endif  // INCLUDE_USEDMEMORY_HPP_
