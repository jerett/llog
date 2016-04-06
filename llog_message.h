//
// Created by jerett on 16/4/6.
//

#ifndef LLOG_LLOG_MESSAGE_H
#define LLOG_LLOG_MESSAGE_H

#include "llog.h"

namespace ins {
class LLogMessage {
public:
  LogMessage(LogLevel level) {
    static const char *level_description[] = {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR",
    };
    oss_ << "[" << level_description[level] << "]";
    oss_ << __FUNCTION__ ;
  }

  LogMessage(const LogMessage&) = delete;
  LogMessage(LogMessage&&) = default;

  ~LogMessage() {
    oss_ << '\n';
    LLog::Instance() << oss_.str();
  }

  inline LogMessage& operator<<(const std::string &msg) {
    oss_ << msg;
    return *this;
  }

private:
  std::ostringstream oss_;
};
}


#endif //LLOG_LLOG_MESSAGE_H
