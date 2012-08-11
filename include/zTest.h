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

#ifndef ZTEST_H__
#define ZTEST_H__

class zLogger;

#include "zCommon.h"
#include "zLogger.h"

/// Test interface.
/// 
/// NOTE: Each test must be self-contained.
/// NOTE: Each test can be executed at random order.
/// @author Matteo Valdina
class zTest {

protected:
  zLogger* logger_;

public:
  zTest(void) {
    logger_ = zLogger::get_logger("test");
  }


  virtual ~zTest(void) {
    logger_->release_reference();
    logger_ = NULL;
  }

  /// Execute the test at given index.
  virtual bool execute(int index) = 0;
  /// Returns the number of test implemented.
  virtual int get_num_tests(void) = 0;
  /// Returns the name of the Test implementation.
  virtual char const* get_name(void) = 0;
  /// Returns the description for the  Test implementation.
  virtual char const* get_description(void) = 0;
  /// Returns the test name at given index.
  virtual char const* get_test_name(int index) = 0;
  /// Returns the test description at given index.
  virtual char const* get_test_description(int index) = 0;
};

#endif

