/******************************************************************************
 * Copyright 2009 Matteo Valdina
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

#ifndef ZSTRINGTOK_H__
#define ZSTRINGTOK_H__

#include "zCommon.h"

#include "zObject.h"
#include "zString.h"
#include "zVectorString.h"

class zStringTokenizer : public zObject {
private:
  zString tokenized_;
  zString tokenizer_;
  bool skipEmptyToken_;
  int currentPos_;
public:
  zStringTokenizer(zString const& tokenized, zString const& tokenizer, bool skipEmptyToken);
  virtual ~zStringTokenizer(void);

  bool hasMoreTokens(void) const;
  zString nextToken(void);

  static zVectorString split(zString const& tokenized, zString const& tokenizer);

};

#endif // ISTRINGTOK_H__
