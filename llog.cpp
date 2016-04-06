//
// Created by jerett on 16/4/5.
//

#include "llog.h"

ins::LogMessage LOG(LogLevel level) {
  return ins::LogMessage(level);
}
