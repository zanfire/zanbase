#include "zVectorReference.h"

#include "zScopeMutex.h"
#include "zMutex.h"


zVectorReference::zVectorReference(bool threadSafe, int initialSize) : zVector(threadSafe, initialSize) {
}


zVectorReference::~zVectorReference(void) {
  // Release all reference and leave the zVector destrocture free the vector.
  for (int i = 0; i < getCount(); i++) {
    zReference* ref = getAt(i);
    ref->release();
  }

}

void zVectorReference::append(zReference* element) {
  zScopeMutex scope(_mtx);
  insertAt(getCount(), element);
}


void zVectorReference::insertAt(int index, zString const& element) {
  zScopeMutex scope(_mtx);
  zString* str = new zString(element);
  zVector::insertAt(index, str);
}


zString zVectorString::getAt(int index) const {
  zScopeMutex scope(_mtx);
  zString* ptr = getAtPtr(index);

  if (ptr != NULL) {
    return zString(ptr);
  }
  return zString();
}


zString* zVectorString::getAtPtr(int index) const {
  zScopeMutex scope(_mtx);
  return (zString*)zVector::getAt(index);
}


zString zVectorString::removeAt(int index) {
  zScopeMutex scope(_mtx);
  zString* ptr = (zString*)zVector::removeAt(index);

  if (ptr == NULL) {
    return zString();
  }
  else {
    zString str(ptr);
    delete ptr;
    return str;
  }
}


int zVectorString::contains(zString const& element) const {
  zScopeMutex scope(_mtx);
  for (int i = 0; i < _count; i++) {
    if (((zString*)_vector[i])->equals(element)) {
      return i;
    }
  }
  return -1;
}


zString zVectorString::toString(zString sep) const {
  zStringBuffer strb;
  for (int i = 0; i < _count; i++) {
    strb.append(*((zString*)_vector[i]));
    if (i < (_count - 1)) {
      strb.append(sep);
    }
  }
  return strb.toString();
}
