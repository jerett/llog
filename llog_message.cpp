//
// Created by jerett on 16/4/6.
//

#include "llog_message.h"
#include "llog.h"

namespace ins{

LLogMessage::~LLogMessage() {
  oss_ << '\n';
  if (level_ >= Configuration::GetInstance().log_level()) {
    LLog::Instance() << oss_.str();
  }
}

}
