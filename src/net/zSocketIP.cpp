#include "zSocketIP.h"

#include "zSocketAddress.h"
#include <errno.h>

zSocketIP::zSocketIP(SocketType type) : zSocketBase(type) {
}


zSocketIP::~zSocketIP(void) {
}



zSocketBase::SocketError zSocketIP::impl_bind(void) {
  if (_desc == INVALID_DESCRIPTOR) return SOCKET_ERROR_CREATE_DESC;
  if (_bindAddress->get_type() != zSocketAddress::ADDRESS_TYPE_IPv4 &&
      _bindAddress->get_type() != zSocketAddress::ADDRESS_TYPE_IPv6) {
    return SOCKET_ERROR_INVALID_ADDRESS;
  }

  int res = bind(_desc, _bindAddress->get_socket_addr(), _bindAddress->get_socket_addr_len());
  if (res == 0) {
    return SOCKET_OK;
  }
  else {
    if (errno == EADDRINUSE) return SOCKET_ERROR_BINDTO_ADDRESS_ALREADY_IN_USE;
    if (errno == EACCES) return SOCKET_ERROR_BINDTO_NO_PERMISSION;
    return SOCKET_ERROR_BINDTO;
  }
}


zSocketBase::SocketError zSocketIP::impl_close(void) {
 int how = 0;
#if defined(_WIN32)
  how = SD_BOTH;
#else
  how = SHUT_RDWR;
#endif
  int ret = shutdown(_desc, how);
  if (ret == -1) {
    // TODO: Handle errors.
  }
  return SOCKET_OK;
}
