// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>

#include "Histogram.hpp"

void Histogram::OnDataLoaded(const std::vector<Item>&,
                             const std::vector<Item>& new_items) {
  Log::get_instance().WriteDebug("Histogram::OnDataLoaded");
  _avg = 0;
  size_t i = 0;
  for (i; i < new_items.size(); ++i) {
    _avg += new_items[i].score;
  }

  _avg /= static_cast<float>(i);
  Log::get_instance().Write("Current average = " + std::to_string(_avg));
}
void Histogram::OnSkipped(const Item&) {
  Log::get_instance().WriteDebug("Histogram::OnSkipped");
  _skipped++;
}
