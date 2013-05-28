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
#include "zArray.h"


/// This class tokenize a string in substring.
///
/// NOTE
/// Late parsing? Parsing only when is requested a token and not at the startup?
/// Personally I don't appreciate the has_more_tokens and next I hate them...
/// But permits a late parsing.
/// For fast and bla bla features use directly the the index of ...
/// Or delete this class? Provides only split method?
/// Or improves this class with incredible features for the parsing of text message.
/// like INVITE.
/// It isn't a string tokenizer but a string parser.
//
/// DEATH class!
///
/// @author Matteo Valdina
class zStringTokenizer {
protected:
  zString _tokenized;
  zString _tokenizer;
  bool _skipEmptyToken;
  int _currentPos;

public:
  zStringTokenizer(zString const& tokenized, zString const& tokenizer, bool skipEmptyToken);
  virtual ~zStringTokenizer(void);
 
  /// Returns true if it is available more tokens.
  bool has_more_tokens(void) const;
  /// Returns the next tokens and move internal pos to the next one.
  zString next(void);
};

#endif // ZSTRINGTOK_H__
