/******************************************************************************
 * Copyright 2012 Matteo Valdina
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

#ifndef ZVECTORREFERENCE_H__
#define ZVECTORREFERENCE_H__

#include "global.h"

#include "zVector.h"

/// zVectorReference is a specialized vector for zReference object.
/// The main goals are:
///  - Automatic acquire/release of reference to improve readability of code.
///  
/// @author Matteo Valdina
class zVectorReference : private zVector {

public:
  zVectorReference(bool threadSafe = false, int initialSize = VECTOR_SIZE_INCREMENT);
  virtual ~zVectorReference(void);

  int getCount(void) const { return zVector::getCount(); }

  void append(zReference* element);
  void insertAt(int index, zReference* element);
  zReference* getAt(int index) const;

  /// @remarks the returned object could be destroyed.
  zReference* removeAt(int index);
};

#endif

