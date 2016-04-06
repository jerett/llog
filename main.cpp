
#include "llog.h"
#include <thread>

int main() {
  auto &config = ins::Configuration::GetInstance();
  config.Configure(ins::Configuration::LOG_FILE, "/tmp/test.log");
  config.Configure(ins::Configuration::LOG_LEVEL, "ERROR");
  LOG(INFO) << "中文" << "  bbbb";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ins::log_to_stderr = true;
  LOG(ERROR) << "cccc" << "  dddd";
  return 0;
}

