#include "zScopeMutex.h"

#include "zMutex.h"

zScopeMutex::zScopeMutex(zMutex* mtx) {
  _mtx = mtx;
  if (_mtx != NULL) _mtx->lock();
}


zScopeMutex::zScopeMutex(zMutex& mtx) {
  _mtx = &mtx;
  if (_mtx != NULL) _mtx->lock();
}


zScopeMutex::~zScopeMutex(void) {
  if (_mtx != NULL) _mtx->unlock();
}
