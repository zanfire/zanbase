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

#ifndef ZRECT_H__
#define ZRECT_H__

#include "zCommon.h"

/// @author Matteo Valdina
class zRect {

public:
  int left;
  int top;
  int right;
  int bottom;

public:
  zRect(void);
  zRect(int left, int top, int right, int bottom);
  ~zRect(void);

  int width(void) const { return right - left; }
  int height(void) const { return bottom - top; }

  static zRect scale(zRect area, zRect rc);
  static zRect center(zRect area, zRect rc);
};

#endif // ZRECT_H__
