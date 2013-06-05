/******************************************************************************
 * Copyright 2009-2013 Matteo Valdina
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


class zEvent;

/// Interface for a runnable object.
/// The implementor must implement run method to execute somethings.
/// @remarks If you need a runnable object that execute a loop you should use zRunnableLoop.
class zRunnable {
public:
  zRunnable(void);
  virtual ~zRunnable(void);

  /// This method is called by the executor (ex: zThread).
  virtual int run(void* param) = 0;
};

/// Interface for a runnable object that it implements a loop. 
class zRunnableLoop : public zRunnable {
protected:
  /// 
  bool _must_continue;
  zEvent* _continue;
  int _loop_timeout_ms;
  THREAD_ID _threadID;


public:
  zRunnableLoop(void);
  virtual ~zRunnableLoop(void);

  /// Configure the loop timeout in milliseconds. A value of -1 means an infinite timeout.
  void set_loop_timeout(int ms);
  /// Signals to the loop to run, ignoring the timeout.
  void signal_continue(void);
  /// It stops the loop of of the run method.
  void stop(bool sync);
  /// Function called by the executor (ex: zThread).
  /// NOTE: This method should not be implemented by derived classes.
  virtual int run(void* param);
  /// Interface 
  /// This method is called every _loop_timeout_ms or when the _continue event is triggered.
  virtual int execute(void* param) = 0;
};


#endif // ZRUNNABLE_H__
