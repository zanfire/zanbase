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

#include "zStringTokenizer.h"

zStringTokenizer::zStringTokenizer(zString const& tokenized, zString const& tokenizer, bool skipEmptyToken) : zObject() {
  tokenized_ = tokenized;
  tokenizer_ = tokenizer;
  skipEmptyToken_ = skipEmptyToken;
  currentPos_ = 0;
}
  

zStringTokenizer::~zStringTokenizer(void) {
}


bool zStringTokenizer::hasMoreTokens(void) const {
  return currentPos_ < tokenized_.get_length();
}


zString zStringTokenizer::nextToken(void) {
  int start = currentPos_;
  currentPos_ = tokenized_.index_of(tokenizer_, currentPos_);
  currentPos_ = (currentPos_ == -1) ? tokenized_.get_length() : currentPos_;
  if (start == currentPos_ && skipEmptyToken_) {
    return nextToken();
  }
  else {
    int length = currentPos_++ - start;
    return tokenized_.substring(start, length);
  }
}

