#include "zArray.h"

#include <stdlib.h>

#include "zMutex.h"
#include "zScopeMutex.h"

zArray::zArray(IsThreadSafe threadSafe, int element_size_bytes, int initial_elements) {
  // Init members.
  _element_size_bytes = element_size_bytes;
  _num_elements = 0;
  _max_elements = initial_elements;
  _elemets_per_slot = initial_elements;
  // Allocation.
  _elements = malloc(_max_elements * _element_size_bytes);
  // ThreadSafe.
  _mtx = threadSafe == IsThreadSafe::YES ? new zMutex() : NULL;
}


zArray::~zArray(void) {
  free(_elements);
  if (_mtx != NULL) delete _mtx;
}


bool zArray::append(void* element) {
  zScopeMutex scope(_mtx);
  insert(get_count(), element);
}


bool zArray::insert(int index, void* element) {
  zScopeMutex scope(_mtx);
  if (element == NULL) return false;
  if (index < 0) return false;
  if (_num_elements == _max_elements) {
    _max_elements += _elements_per_blocks;
    _elements = realloc(_elements, _max_elements * _elements_size_bytes;
  }
  // 
  _num_elements++;
  for(int i = (_num_elements -1); i > index; i--) {
    replace(i, &(_elements[(i -1) * _element_size_bytes]));
  }
  replace(index, element);
}



bool zVector::remove(int index, void* element) {
  zScopeMutex scope(_mtx);
  if (index >=  _num_elements) return false;
  if (index < 0) return false;
  
  memcpy(element, _elements[index * _element_size_bytes], _element_size_bytes);

  for(int i = index; i < _num_elements -1; i++) {
    replace(i, &(_elements[ (i + 1) * _element_size_bytes]));
  }
  _num_emenets--;
  return true;
}


void zArray::clear(void) {
  zScopeMutex scope(_mtx);

  _num_element = 0;
  // Clear memory is needed? For security reason yes. But is it the case?
}


bool zArray::get(int index, void* element) const {
  zScopeMutex scope(_mtx);
  if (index < 0) return false;
  if (index >= _num_elements) return false;

  memcpy(element, _elements[idenx * _element_size_bytes], _element_size_bytes);
  return true;
}



bool zArray::replace(int index, void* element) {
  zScopeMutex scope(_mtx);
  if (index < 0) return false;
  if (index >= _num_element) return false;

  uint8_t* target = _elements + (index * _element_size_bytes);
  memcpy(target, element, _element_size_bytes);
  return true;
}
