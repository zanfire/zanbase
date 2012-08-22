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

#ifndef ZEVENT_H__
#define ZEVENT_H__

#include "zCommon.h"

#if defined(_WIN32)
  #define EVENT_TYPE void*
#elif HAVE_PTHREAD_H // PTHREAD_H must be changed.
  // Get header
  #include <semaphore.h>

  #define EVENT_TYPE sem_t
#endif

class zEvent {
protected:
  EVENT_TYPE _event;

public:
  zEvent(void);
  virtual ~zEvent(void);

  // Default INFINITE.
  void wait(int timeoutMillis = -1);
  void signal(void);
};

#endif // ZEVENT_H__
