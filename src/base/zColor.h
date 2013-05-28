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

#ifndef ZCOLOR_H__
#define ZCOLOR_H__

#include "zCommon.h"

/// @author Matteo Valdina
class zColor {
protected:
  zColor(void) {}
  virtual ~zColor(void) {}
};


class zSolidColor : public zColor {
protected:
  unsigned char _r;
  unsigned char _g;
  unsigned char _b;
  unsigned char _a;

public:
  zSolidColor(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255);
  virtual ~zSolidColor(void);

  float get_float_r(void) { return _r / 255.0f; }
  float get_float_g(void) { return _g / 255.0f; }
  float get_float_b(void) { return _b / 255.0f; }
  float get_float_a(void) { return _a / 255.0f; }

  unsigned char get_r(void) { return _r; }
  unsigned char get_g(void) { return _g; }
  unsigned char get_b(void) { return _b; }
  unsigned char get_a(void) { return _a; }

};


#endif // ZCOLOR_H__
