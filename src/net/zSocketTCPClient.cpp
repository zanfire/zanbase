#include "zSocketTCPClient.h"

#include "zSocketAddressIPv4.h"
#include "zSocketAddressIPv6.h"


zSocketTCPClient::zSocketTCPClient(SOCKET_DESC desc, zSocketAddress* localAddress, sockaddr const& fromAddr, int fromAddrLen) {
  _desc = desc;
  // TODO: wrong!!
  _bindAddress = localAddress->clone();
  if (localAddress->getType() == zSocketAddress::ADDRESS_TYPE_IPv4) {
    sockaddr_in* addr = (sockaddr_in*)&fromAddr;
    _remoteAddress = new zSocketAddressIPv4(*addr);
  }
  else {
    sockaddr_in6* addr = (sockaddr_in6*)&fromAddr;
    _remoteAddress = new zSocketAddressIPv6(addr->sin6_addr);
  }
}


zSocketTCPClient::~zSocketTCPClient(void) {
}
