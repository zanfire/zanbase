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

#ifndef ZOBJECT_H__
#define ZOBJECT_H__

#include "zCommon.h"
#include "zReference.h"

/// This class provides an interface/implementation reference system.
/// 
/// @author Matteo Valdina
class zObject {

protected:
  zReference _reference;

public:

  /// Acquire a reference.
  virtual zref_t acquire_reference(void);
  /// Release a reference.
  /// The last reference cause the destruction of the instance.
  virtual zref_t release_reference(void);

  inline zref_t get_reference_count(void) { return _reference.get_count(); }

protected:
  /// Ctor is protected because the zObject base class cannot be instantiated.
  zObject(void);
  /// Dtor is protected because the instance must be destroyed with the last
  /// release_reference invoke.
  virtual ~zObject(void);
};

#endif // ZOBJECT_H__

