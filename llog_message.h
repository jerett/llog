//
// Created by jerett on 16/4/6.
//

#ifndef LLOG_LLOG_MESSAGE_H
#define LLOG_LLOG_MESSAGE_H

#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

namespace ins {
class LLogMessage {
public:
  LLogMessage(const std::string &file,
              const std::string &function,
              int line,
              int level) : level_(level){
    static const char *level_description[] = {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR",
    };

    auto now = std::chrono::system_clock::now();
    auto log_time_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto now_c = std::chrono::system_clock::to_time_t(log_time_ms);
    struct tm *local_tm = std::localtime(&now_c);
    auto time = std::put_time(std::localtime(&now_c), "%m-%d %T");
    oss_ << '[' << level_description[level];
    oss_ << ' ' << time << '.' << log_time_ms.time_since_epoch().count()%1000;

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
  LLogMessage(LLogMessage&&) = default;

  ~LLogMessage();

  inline LLogMessage& operator<<(const std::string &msg) {
    oss_ << msg;
    return *this;
  }

private:
  std::ostringstream oss_;
  int level_;
//  std::string file_;
//  std::string function_;
//  int line_;
};
}


#endif //LLOG_LLOG_MESSAGE_H
