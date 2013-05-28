#include "zSocketAddress.h"

#include "zSocketAddressIPv4.h"
#include "zSocketAddressIPv6.h"

#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#if HAVE_SYS_TYPES_H
#  include <sys/types.h>
#endif

zSocketAddress::zSocketAddress(AddressType type) {
  _type = type;
}


zSocketAddress::~zSocketAddress() {
}


zSocketAddress* zSocketAddress::createSocketAddressFromString(zString const& str, int port) {
  in_addr addr;
  int res = inet_pton(AF_INET, str.get_buffer(), &addr);
  if (res == 1) {
    return new zSocketAddressIPv4(ntohl(addr.s_addr), port);
  }
  in6_addr addr6;
  res = inet_pton(AF_INET6, str.get_buffer(), &addr6);
  if (res == 1) {
    return new zSocketAddressIPv6(addr6);
  }

  return NULL;
}
