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

#ifndef ZTESTER_H__
#define ZTESTER_H__

#include "global.h"

class zVector;
class zTest;

/// This class execute a set of test. 
/// @author Matteo Valdina
class zTester {

protected:
  /// The set of tests that they will execute by the Tester.
  zVector* _testSetUnprocessed;
  /// The set of tests that they ware exectued by the Tester.
  zVector* _testSetProcessed;

public:
  zTester(void);
  virtual ~zTester(void);

  /// Add a test to the test set.
  /// @remarks This test will be executed in the insertion order.
  void add(zTest* test);

  /// Tester processes the test set.
  /// @return TODO: define if needed a expressive return code.
  bool process(void);

  zVector* getUnprocessedTest(void) { return _testSetUnprocessed; }
  zVector* getProcessedTest(void) { return _testSetProcessed; }
};

#endif

