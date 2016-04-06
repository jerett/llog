
#include "llog.h"
#include <thread>

void test() {
  auto &config = ins::Configuration::GetInstance();
//  config.Configure(ins::Configuration::LOG_FILE, "/tmp/test.log");
  config.Configure(ins::Configuration::LOG_LEVEL, "DEBUG");
  LOG(INFO) << "中文" << "  bbbb";
  LOG_IF(WARNING, 2 > 1) << "fuck UUUUUUUUU";
  CHECK(1==2) << "fuckkkkkkkkk" << " 222";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  ins::log_to_stderr = true;
  LOG(ERROR) << "cccc" << "  dddd";
}

void count() {
  for (int i = 0 ; i < 99; ++i) {
    LOG(INFO) << i;
    CHECK(i < 90) << " meet 90 first i:" << i;
  }
};

int main() {
//  std::thread test_thread(test);
//  test_thread.join();

  std::thread count_thread1(count), count_thread2(count);
  count_thread1.join();
  count_thread2.join();
//  test();
  return 0;
}

