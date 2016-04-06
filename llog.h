//
// Created by jerett on 16/4/5.
//

#ifndef LLOG_LLOG_H
#define LLOG_LLOG_H

#include <string>
#include <sstream>
#include <iostream>
#include <memory>

//#define LOG(LEVEL)

namespace ins {
class LogMessage;
}

enum LogLevel {
  DEBUG = 0,
  INFO,
  WARNING,
  ERROR,
};

ins::LogMessage LOG(LogLevel level);

namespace ins{

class LLog {
public:
  static LLog& Instance() {
    static LLog llog;
    return llog;
  }

  LLog(const LLog&) = delete;
  LLog(LLog&&) = delete;
  LLog operator=(const LLog&) = delete;

  inline LLog& operator<<(const std::string &msg) {
    std::cout << msg;
    return *this;
  }

private:
  LLog() {}
};


}


#endif //LLOG_LLOG_H
