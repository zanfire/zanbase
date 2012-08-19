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

#ifndef ZTHREAD_H__
#define ZTHREAD_H__

#include "zCommon.h"
#include "zObject.h"

class zRunnable;
class zThreadMain;

#include "zMutex.h"
#include "zEvent.h"

/// A Thread wrapper over the system threads.
/// @author Matteo Valdina
class zThread : public zObject {
  // zThreadMain is a local class used to start the zRunnable.
  // It is friend class that can access and set internal variables of zThread.
  friend class zThreadMain;

protected:
  // Implementation used by the zThread.
  zRunnable* _runnable;
  // Platform specific thread handle.
  THREAD _thread;
  // The thread ID.
  THREAD_ID _id;
  void* _app_param;
  zMutex _mtx_running;
  int _stack_size;
  /// It is the result code of the thread function.
  int _result;
  volatile bool _is_running;
  // event that is triggered when thread is started.
  zEvent _ev_start;

public:
  zThread(zRunnable* runnable, int stack_size = 1024 * 2048);
  virtual ~zThread(void);

  /// Sleep for the amount of milliseconds.
  static void sleep(int ms);
  /// Return the current thread ID.
  static THREAD_ID get_current_thread_id(void);
  
  /// Returns the thread id.
  THREAD_ID get_thread_id(void) {return _id; }

  /// Start the thread.
  /// NOTE: If the thread is running this function returns false.
  /// You can run multiple times the same function.
  bool start(void* param = NULL);

  /// Returns the runnable.
  zRunnable* get_runnable(void) const { return _runnable; }

  /// Returns true if the zRunnable instance is running.
  bool running(void) const { return _is_running; }

  /// Join the running thread.
  /// Returns the result of thread function.
  int join(void);
};

#endif // ZTHREAD_H__

