// Copyright 2022 VladislavRz <rzhevskii_vladislav@mail.ru>

#ifndef INCLUDE_LOG_HPP_
#define INCLUDE_LOG_HPP_

#include <iostream>
#include <string>
#include <fstream>

class Log {
 private:
  Log();

 public:
  Log(const Log&) = delete;
  Log& operator=(const Log&) = delete;
  ~Log() = default;

 public:
  static Log& get_instance();

 public:
  void Write(std::string_view message) const;
  void WriteDebug(std::string_view message) const;
  void SetLogLvl(size_t lvl) { _level = lvl; }

 private:
  size_t _level;
  mutable std::ostream* _out;
};

#endif  // INCLUDE_LOG_HPP_
