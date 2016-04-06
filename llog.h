//
// Created by jerett on 16/4/5.
//

#ifndef LLOG_LLOG_H
#define LLOG_LLOG_H

#include <string>
#include <iostream>
#include <sstream>
#include <mutex>
#include <memory>

#include "llog_message.h"

#if defined(_WIN32) || defined(_WIN64)
#   define ELPP_OS_WINDOWS 1
#endif

#define LOG(level) \
  if (level >= ins::Configuration::GetInstance().log_level()) \
    ins::Log(__FILE__, __FUNCTION__, __LINE__ , level) \

#define LOG_IF(level, expression) \
  if (true == expression) \
    LOG(level)

#define CHECK(expression) \
  if (false == (expression)) \
    ins::FatalLog(#expression, __FILE__, __FUNCTION__, __LINE__)

namespace ins {
class LLogMessage;
extern bool log_to_stderr;
}

enum LogLevel {
  DEBUG = 0,
  INFO,
  WARNING,
  ERROR,
};

namespace ins{

LLogMessage Log( const char *file,
                 const char *function,
                 int line,
                 LogLevel level);

LLogMessage FatalLog(const char *expression,
                     const char *file,
                     const char *function,
                     int line);
//ins::LLogMessage Log_if(bool condition,
//                        const char *file,
//                        const char *function,
//                        int line,
//                        LogLevel level);

class Configuration {
public:
  enum {
    LOG_LEVEL = 0,
    LOG_FILE,
  };

  static Configuration& GetInstance() noexcept {
    static Configuration configuration;
    return configuration;
  }

  Configuration(const Configuration&) = delete;
  Configuration(Configuration&&) = delete;

  bool Configure(int type, const std::string &val) noexcept ;

  LogLevel log_level() const noexcept {
    return log_level_;
  }

private:
  Configuration() = default;

private:
  std::string log_file_;
  LogLevel  log_level_ = DEBUG;
};

class LLog {
public:
  static LLog& Instance() noexcept {
    static LLog llog;
    return llog;
  }

  ~LLog() {
    if (log_file_) {
      fclose(log_file_);
    }
  }

  bool DupLogToFile(const std::string &file) noexcept ;

  LLog(const LLog&) = delete;
  LLog(LLog&&) = delete;

  inline LLog& operator<<(const std::string &msg) {
#ifdef ELPP_OS_WINDOWS
    std::lock_guard<std::mutex> lck(mtx_);
#endif
    (log_to_stderr ? std::cerr : std::cout) << msg;
    if (log_file_ != nullptr) {
      fwrite(msg.c_str(), 1, msg.length(), log_file_);
      fflush(log_file_);
    }
    return *this;
  }

private:
  LLog() {}
  FILE *log_file_ = nullptr;
#ifdef ELPP_OS_WINDOWS
  std::mutex mtx_;
#endif
};

}


#endif //LLOG_LLOG_H
