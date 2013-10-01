#include "zSocketBase.h"
#include "zSocketAddress.h"

#include <unistd.h>
#include <fcntl.h>


zSocketBase::zSocketBase(SocketType type) : zObject() {
  _type = type;
}


zSocketBase::~zSocketBase(void) {
}


zSocketBase::SocketError zSocketBase::bindTo(zSocketAddress const& address) {
  if (_desc != INVALID_DESCRIPTOR) {
    // Destroy socket descriptor and close socket.
  }
  _bindAddress = address.clone();
  SocketError res = impl_create();
  if (res != SOCKET_OK) return res;
  if (_desc == INVALID_DESCRIPTOR) {
    return SOCKET_ERROR_CREATE_DESC;
  }

  return impl_bind();
}


zSocketBase::SocketError zSocketBase::close(void) {
  if (_desc != INVALID_DESCRIPTOR) return SOCKET_ERROR_GENERIC;

  return impl_close();
}


bool zSocketBase::set_non_blocking(bool blocking) {
  
  fcntl(_desc, F_SETFL, O_NONBLOCK);
  return true;
}


char const* zSocketBase::getErrorDescription(zSocketBase::SocketError error) {
  switch (error) {
    case SOCKET_OK:                                     return "No error";
    case SOCKET_ERROR_NOMEM:                            return "No sufficient memory available";
    case SOCKET_ERROR_GENERIC:                          return "Undefined error";
    case SOCKET_ERROR_CREATE_DESC:                      return "Failed to create socket";
    case SOCKET_ERROR_BINDTO:                           return "Failed bind";
    case SOCKET_ERROR_BINDTO_ADDRESS_ALREADY_IN_USE:    return "Address already in use";
    case SOCKET_ERROR_BINDTO_NO_PERMISSION:             return "No permission bind address";
    case SOCKET_ERROR_INVALID_ADDRESS:                  return "Invalid address";
    default:                                            return "Unknown error";
  }
}
