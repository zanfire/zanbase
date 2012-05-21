/******************************************************************************
 * Copyright 2009 - 2012 Matteo Valdina
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

#ifndef ZREFERENCE_H__
#define ZREFERENCE_H__

#include "zCommon.h"

/// This class provides a reference counter with
/// atomic operation.
///
/// This class can not be derived.
/// This class is thread-safe.
/// @author Matteo Valdina
class zReference {

private:
	volatile zref_t _count;
public:
  zReference(void);
  ~zReference(void);

  zref_t increment(void);
  zref_t decrement(void);

  inline zref_t get_count(void) const { return _count; }
};

#endif // ZREFERENCE_H__

