#include "zReference.h"


zReference::zReference(void) {
  _count = 0;
  increment();
}


zReference::~zReference(void) {
}


zref_t zReference::increment(void) {
  return ATOMIC_INC(_count);
}


zref_t zReference::decrement(void) {
  return ATOMIC_DEC(_count);
}

