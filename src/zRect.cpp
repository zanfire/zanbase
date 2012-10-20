/******************************************************************************
 * Copyright 2009-2011 Matteo Valdina
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

#include "zRect.h"


zRect::zRect(void) {
  left = 0;
  top = 0;
  right = 0;
  bottom = 0;
}

zRect::zRect(int left, int top, int right, int bottom) {
  this->left = left;
  this->top = top;
  this->right = right;
  this->bottom = bottom;
}

zRect::~zRect(void) {
}


zRect zRect::scale(zRect area, zRect rc) {
  zRect res(rc);
  float w = (float)area.width() / (float)rc.width();
  float h = (float)area.height() / (float)rc.height();

  if (w < h) {
    res.right = res.left + (int)(res.width() * w);
    res.bottom = res.top + (int)(res.height() * w);
  }
  else {
    res.right = res.left + (int)(res.width() * h);
    res.bottom = res.top + (int)(res.height() * h);
  }
  return res;
}


zRect zRect::center(zRect area, zRect rc) {
  zRect res(rc);
  if (rc.width() < area.width()) {
    int offset = (area.width() - rc.width()) / 2;
    res.left += offset;
    res.right += offset;
  }
  if (rc.height() < area.height()) {
    int offset = (area.height() - rc.height()) / 2;
    res.top += offset;
    res.bottom += offset;
  }
  return res;
}
