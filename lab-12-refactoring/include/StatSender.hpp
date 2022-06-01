// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>

#ifndef INCLUDE_STATSENDER_HPP_
#define INCLUDE_STATSENDER_HPP_

#include <string_view>
#include <string>
#include <vector>

#include "Observer.hpp"
#include "Log.hpp"

class StatSender: public Observer {
 public:
  StatSender() = default;
  ~StatSender() override = default;

 public:
  void OnDataLoaded(const std::vector<Item>&,
                    const std::vector<Item>& new_items) override;
  void OnRawDataLoaded(const std::vector<std::string> &,
                       const std::vector<std::string> &) override {}
  void OnSkipped(const Item& item) override;

 private:
  virtual void AsyncSend(const std::vector<Item>& items, std::string_view path);

 private:
  std::ofstream _fstr{"network", std::ios::binary};
};

#endif  // INCLUDE_STATSENDER_HPP_
