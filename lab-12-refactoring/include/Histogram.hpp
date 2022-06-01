// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>

#ifndef INCLUDE_HISTOGRAM_HPP_
#define INCLUDE_HISTOGRAM_HPP_

#include <string>
#include <vector>

#include "Observer.hpp"
#include "Log.hpp"

class Histogram: public Observer {
 public:
  Histogram():_avg(0), _skipped(0){}
  ~Histogram() override = default;

 public:
  void OnDataLoaded(const std::vector<Item>&,
                    const std::vector<Item>& new_items) override;
  void OnRawDataLoaded(const std::vector<std::string>&,
                       const std::vector<std::string>&) override{}
  void OnSkipped(const Item&) override;

 public:
  float get_avg() const { return _avg; }
  size_t  get_skipped() const { return _skipped; }

 private:
  float _avg;
  size_t _skipped;
};

#endif  // INCLUDE_HISTOGRAM_HPP_
