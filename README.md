# llog
##introduction
* a small logger support stdout ,file record, and may network later
* written by C++11

##usage
###logging
```
#include "llog.h"
LOG(INFO) << "lllog";
LOG_IF(VERBOSE, 1 > 0) << "expression log";
```
###configuration
* default set to STDOUT, you can switch to STDERR by set 
```
  ins::log_to_stderr = true;
```

* support dup log to file, and set log level
```
  auto &config = ins::Configuration::GetInstance();
  config.Configure(ins::Configuration::LOG_FILE, "/tmp/test.log");
  config.Configure(ins::Configuration::LOG_LEVEL, "ERROR");
```

###CHECK Macro
* used to replace assert. when expression equal false, CHECK will print msg and exit program.
```
  CHECK(1==1) << "1 != 1";
```