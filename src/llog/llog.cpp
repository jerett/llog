//
// Created by jerett on 16/4/5.
//

#include "llog.h"

namespace ins{
//ins::LLogMessage Log(LogLevel level) {
//  return ins::LLogMessage(level);
//}
bool log_to_stderr = false;

LLogMessage Log( const char *file,
                 const char *function,
                 int line,
                 LogLevel level) {
  return ins::LLogMessage(file, function, line, level);
}

LLogMessage FatalLog(const char *expression,
                const char *file,
                const char *function,
                int line) {
  return ins::LLogMessage(expression, file, function, line);
}

bool Configuration::Configure(int type, const std::string &val) noexcept {
  switch (type) {
    case LOG_FILE:{
      return LLog::Instance().DupLogToFile(val);
    }
    case LOG_LEVEL:{
      if (val == "VERBOSE") log_level_ = VERBOSE;
      if (val == "INFO") log_level_ = INFO;
      if (val == "WARNING") log_level_ = WARNING;
      if (val == "ERROR") log_level_ = ERROR;
      return true;
    }
    default:
      return false;
  }
}

bool LLog::DupLogToFile(const std::string &file) noexcept {
  log_file_ = fopen(file.c_str(), "a+");
  if (log_file_ == nullptr) {
    std::cerr << " open log file err........" << std::endl;
  }
  return log_file_ == nullptr;
}

}