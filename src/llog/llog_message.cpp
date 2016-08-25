//
// Created by jerett on 16/4/6.
//

#include "llog_message.h"
#include "llog.h"

namespace ins{

LLogMessage::~LLogMessage() {
  oss_ << '\n';
  LLog::Instance() << oss_.str();
  if (fatal_) exit(EXIT_FAILURE);
}

}
