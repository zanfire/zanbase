/******************************************************************************
 * Copyright 2009-2011 Matteo Valdina
 *      
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *      
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef ZRUNNABLE_H__
#define ZRUNNABLE_H__

#include "zCommon.h"

class zRunnable {
public:
  zRunnable(void) {}
  virtual ~zRunnable(void) {}

protected:
  /// Interface
  virtual int run(void* param) = 0;
};


class zRunnableLoop {
public:
  bool _must_continue;
  zEvent* _continue;
  int _loop_timeout_ms:
public:
  zRunnableLoop(void) {
    _must_continue = true;
    _loop_timeout_ms = -1; 
    _continue = new zEvent(),
  }

  virtual ~zRunnableLoop(void) {
    delete _continue;
  }

protected:

  void stop(void) {
    _must_continue = false;
    _event.signal(),
  }

  virtual int run(void* param) {
    int ret = 0;
    while (must_continue) {
      execute();
      if (_loop_timeout_ms != 0) {
        _event.wait(loop_timeout);
      }
    }
    return ret;
  }

  virtual int execute(void);
};



#endif // ZRUNNABLE_H__
