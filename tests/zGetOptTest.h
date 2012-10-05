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

#ifndef ZGETOPTTEST_H__
#define ZGETOPTTEST_H__

#include "zCommon.h"
#include "zTest.h"


/// This class provides the zGetOpt test suite.
/// @author Matteo Valdina
class zGetOptTest : public zTest {

protected:

public:
  zGetOptTest(void);
  virtual ~zGetOptTest(void);
  
  /// zTest implementation.

  virtual bool execute(int index);
  virtual int get_num_tests(void);
  virtual char const* get_name(void);
  virtual char const* get_description(void);
  virtual char const* get_test_name(int index);
  virtual char const* get_test_description(int index);

protected:
  // First test
  bool test_base(void);
};

#endif // ZGETOPTTEST_H__

