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
#include "zMutex.h"
#include "zScopeMutex.h"

#if !defined(DMALLOC)
#  include <stdlib.h>
#endif

/// This class provides an implementation for a dynamic array.
/// DON'T use this class with classes that dtor do somethings...
/// 
/// NOTE: Keep it simple and tiny.
/// @author Matteo Valdina
template <class T>
class zArray {
protected:
  zMutex* _mtx;
  T* _elements;

  int _count;
  int _size;

public:
  /// Default Ctor.
  /// @remarks The default value is copied via memcpy if its contains sone ponter will be copied the address not the content!
  /// 
  /// @param threadSafe is flags to set a thread safe behaviour.
  /// @param element_size_bytes is the size in bytes of each element in the class.
  /// @param elements is the number of initial elements.
  /// @param default value for each element in the array.
  zArray(IsThreadSafe threadSafe, int initial_size) {
    init(threadSafe, initial_size);
  }

  /// Dtor.
  virtual ~zArray(void) {
    //free(_elements);
    delete [] _elements;
    _elements = NULL;
    if (_mtx != NULL) delete _mtx;
  }


  /// Copy ctors
  zArray(zArray<T> const& obj) {
    init((obj._mtx != NULL) ? YES : NO, obj._count );
    
    copy_from(obj);
  }


  zArray& operator=(zArray<T> const& rhs) {
    if (this != &rhs) {
      copy_from(rhs);
    }
    return *this;
  }

  void lock(void) {
    if (_mtx != NULL) _mtx->lock();
  }
  

  void unlock(void) {
    if (_mtx != NULL) _mtx->unlock();
  }
  
  /// Get count of elements.
  int get_count(void) const { return _count; }

  /// Append an element at the end of array.
  bool append(T element) { 
    zScopeMutex scope(_mtx);
    return insert(get_count(), element);
  }

  /// Insert an element at the given index.
  bool insert(int index, T element) {
    zScopeMutex scope(_mtx);

    if (_count + 1 > _size) {
      // TODO: this code must be improved.
      if (!resize(_size + 1024)) {
        // TODO: Handle error!!!
        return false;
      }
    }

    for (int i = _count; i > index; i--) {
      _elements[i + 1] = _elements[i];
    }

    _elements[index] = element;
    _count++;
    return true;
  }
  
  /// Remove an element at the given index.
  /// @param index is the index of removed element.
  /// @param element 
  bool remove(int index, T* element) {
    zScopeMutex scope(_mtx);
    if (index < 0 || index >= _count) return false;

    if (element != NULL) {
      *element = _elements[index];
    }
    _count--;
    for (int i = index; i < _count; i++) {
      _elements[i] = _elements[i + 1];
    }
    return true;
  }
  
  
  /// Get an element at the given index.
  bool get(int index, T* element) const {
    zScopeMutex scope(_mtx);
    if (index < 0 || index >= _count) return false;
    
    *element = _elements[index];
    return true;
  }


  bool resize(int new_size) {
    // NOTE: This way is less efficent of a realloc because it doesn't extends the current memory chunk.
    T* tmp = new T[new_size];
    if (tmp == NULL) {
      return false;
    }
    else {
      for (int i = 0; i < _size; i++) {
        tmp[i] = _elements[i];
      }
      delete [] _elements;
      _elements = tmp;
    }
    _size = new_size;
    return true;
  }


  /// Copy the content from argument into the array.
  void copy_from(zArray<T> const& arr) { 
    zScopeMutex scope(_mtx);
    for (int i = 0; i < arr.get_count(); i++) {
      T element;
      if (arr.get(i, &element)) {
        append(element);
      }
    }
  }

 protected:
  void init(IsThreadSafe threadSafe, int initial_size) {
    _mtx = threadSafe == YES ? new zMutex() : NULL;
    if (initial_size <= 0) initial_size = 32;
    _size = initial_size;
    _count = 0;
    _elements = new T[_size];
  }
};

#endif // ZARRAY_H__
