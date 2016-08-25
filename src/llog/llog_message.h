//
// Created by jerett on 16/4/6.
//

#ifndef LLOG_LLOG_MESSAGE_H
#define LLOG_LLOG_MESSAGE_H

#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <thread>

namespace ins {
class LLogMessage {
public:
  LLogMessage(const std::string &file,
              const std::string &function,
              int line,
              int level){
    static const char *level_description[] = {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR",
    };

    auto now = std::chrono::system_clock::now();
    auto log_time_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto now_c = std::chrono::system_clock::to_time_t(log_time_ms);
    auto local_time = std::localtime(&now_c);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%m-%d %T", local_time);
    auto id = std::this_thread::get_id();
    oss_ << '[' << id << ']';
    oss_ << '[' << level_description[level];
    oss_ << ' ' << time_str << '.' << log_time_ms.time_since_epoch().count()%1000;

    auto pos = file.find_last_of('/');
    if (pos != std::string::npos) {
      auto filename = file.substr(pos+1);
      oss_ << ' ' << filename;
      oss_ << ':' << line << ']';
    } else {
      oss_ << ' ' << file;
      oss_ << ':' << line << ']';
    }
  }

  LLogMessage(const std::string &expression,
              const std::string &file,
              const std::string &function,
              int line):fatal_(true) {
    auto now = std::chrono::system_clock::now();
    auto log_time_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto now_c = std::chrono::system_clock::to_time_t(log_time_ms);
    auto local_time = std::localtime(&now_c);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%m-%d %T", local_time);
    auto id = std::this_thread::get_id();
    oss_ << '[' << id << ']';
    oss_ << '[' << "Check failed (" << expression << ')';
    oss_ << ' ' << time_str << '.' << log_time_ms.time_since_epoch().count()%1000;

    auto pos = file.find_last_of('/');
    if (pos != std::string::npos) {
      auto filename = file.substr(pos+1);
      oss_ << ' ' << filename;
      oss_ << ':' << line << ']';
    } else {
      oss_ << ' ' << file;
      oss_ << ':' << line << ']';
    }
  }

  LLogMessage(const LLogMessage&) = delete;
  LLogMessage(LLogMessage &&rhs) = delete;
  LLogMessage& operator=(const LLogMessage&) = delete;
  LLogMessage& operator=(LLogMessage&&) = delete;
  ~LLogMessage();

  template <typename T>
  inline LLogMessage& operator<<(const T &msg) {
    oss_ << msg;
    return *this;
  }

  std::ostringstream& oss() noexcept {
    return oss_;
  }

private:
  std::ostringstream oss_;
  bool fatal_ = false;
//  int level_;
//  std::string file_;
//  std::string function_;
//  int line_;
};
}


#endif //LLOG_LLOG_MESSAGE_H
