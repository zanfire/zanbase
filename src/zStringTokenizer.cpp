#include "zStringTokenizer.h"

zStringTokenizer::zStringTokenizer(zString const& tokenized, zString const& tokenizer, bool skipEmptyToken) {
  _tokenized = tokenized;
  _tokenizer = tokenizer;
  _skipEmptyToken = skipEmptyToken;
  _currentPos = 0;
}
  

zStringTokenizer::~zStringTokenizer(void) {
}


bool zStringTokenizer::has_more_tokens(void) const {
  // If current pos is less than max length exists at least one tokens?
  // TODO: It is bugged!
  return _currentPos < _tokenized.get_length();
}


zString zStringTokenizer::next(void) {
  int start = _currentPos;
  _currentPos = _tokenized.index_of(_tokenizer, _currentPos);
  if (_currentPos == -1) {
    _currentPos = _tokenized.get_length(); 
  }
  else {
    _currentPos++;
  }
  if (start == _currentPos && _skipEmptyToken) {
    return next();
  }
  else {
    int length = _currentPos - start;
    return _tokenized.substring(start, length);
  }
}

