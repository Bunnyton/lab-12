// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>

#include "StatSender.hpp"

void StatSender::OnDataLoaded(const std::vector<Item>&,
                              const std::vector<Item>& new_items) {
  Log::get_instance().WriteDebug("StatSender::OnDataLoaded");
  AsyncSend(new_items, "/items/loaded");
}

void StatSender::OnSkipped(const Item& item) {
  Log::get_instance().WriteDebug("StatSender::OnSkipped");
  AsyncSend({item}, "/items/skiped");
}

void StatSender::AsyncSend(
    const std::vector<Item>& items,
    std::string_view path) {
  Log::get_instance().Write(path);
  Log::get_instance().Write("send stat " + std::to_string(items.size()));

  for (const auto& item : items) {
    Log::get_instance().WriteDebug("send: " + item.id);
    _fstr << item.id << item.name << item.score;
    _fstr.flush();
  }
}
