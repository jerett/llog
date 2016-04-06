#include "llog.h"

int main() {
  LOG(INFO) << "中文" << "  bbbb";
  LOG(INFO) << " cccc" << "  dddd";
  return 0;
}