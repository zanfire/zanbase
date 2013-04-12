/******************************************************************************
 * Copyright 2009 2012 Matteo Valdina
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

#ifndef ZBUFFERTEST_H__
#define ZBUFFERTEST_H__

#include "zCommon.h"
#include "zTest.h"


/// This class provides a the test implementation for zBuffer.
/// @author Matteo Valdina
class zBufferTest : public zTest {

protected:

public:
  zBufferTest(void);
  virtual ~zBufferTest(void);
  
  /// zTest implementation.

  virtual bool execute(int index);
  virtual int get_num_tests(void);
  virtual char const* get_name(void);
  virtual char const* get_description(void);
  virtual char const* get_test_name(int index);
  virtual char const* get_test_description(int index);

protected:
  bool test_ctor(void);
  bool test_resize(void);
  bool test_append(void);
  bool test_set(void);
};

#endif // ZBUFFERTEST_H__

