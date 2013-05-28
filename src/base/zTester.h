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

#include "zCommon.h"

#include "zArray.h"

class zTest;

/// This class execute a set of test. 
/// @author Matteo Valdina
class zTester {

protected:
  /// Tests
  zArray<zTest*> _tests;

public:
  zTester(void);
  virtual ~zTester(void);

  /// Add a test to the test set.
  /// @remarks This test will be executed in the insertion order.
  void add(zTest* test);

  /// Remove a test from the test set.
  zTest* remove(int index);

  int get_count(void) const { return _tests.get_count(); }

  /// Tester processes the test set.
  /// @return TODO: define if needed a expressive return code.
  bool process(void);
  //// Tester interacts via the console to choose the executed tests.
  bool process_interactive(void);

protected:
  // Execute the test at given index.
  // This method handles the gui and invoke the test method.
  bool execute(zTest* test, int index);
};

#endif

