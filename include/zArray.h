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

#ifndef ZARRAY_H__
#define ZARRAY_H__

#include "zCommon.h"

class zMutex;

/// This class provides an implementation for dynamic array. 
/// Each element have the same and fixed size.
/// 
/// NOTE: Keep it simple and tiny.
/// @author Matteo Valdina
class zArray {
protected:
  zMutex* _mtx;
  uint8_t* _elements;
  int _element_size_bytes;
  int _num_elements;
  int _max_elements;
  /// Number of elements allocated per each memory block.
  int _elements_per_block;

public:
  /// Default Ctor.
  /// @param threadSafe is flags to set a thread safe behaviour.
  /// @param element_size_bytes is the size in bytes of each element in the class.
  /// @param elements is the number of initial elements.
  zArray(IsThreadSafe threadSafe, int element_size_bytes, int initial_elements);

  /// Dtor.
  virtual ~zArray(void);

  /// Get count of elements.
  int get_count(void) const { return _num_elements; }

  /// Append an element at the end of array.
  bool append(void* element);
  /// Insert an element at the given index.
  bool insert(int index, void* element);
  /// Remove an element at the given index.
  /// @param index is the index of removed element.
  /// @param element is a pointer where is copied the content of removed element.
  bool remove(int index, void* element = NULL);
  /// Remove all elements.
  void clear(void);
  /// Get an element at the given index.
  bool get(int index, void* element) const;

  bool replace(int index, void* element);
};

#endif

