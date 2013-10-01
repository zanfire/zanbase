#include "zSocketUDP.h"

#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <errno.h>

#include <stdio.h>

zSocketUDP::zSocketUDP(void) : zSocketIP(zSocketBase::SOCKET_TYPE_UDP) {
}


zSocketUDP::~zSocketUDP(void) {
}


int zSocketUDP::writeBytes(unsigned char* buffer, int bufferSize, uint32_t ip, uint16_t port) {
  sockaddr_in addr;
  memset(&addr, 0x0, sizeof(sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(ip);
  addr.sin_port = htons(port);
  int rc = sendto(_desc, buffer, bufferSize, 0, (sockaddr*)&addr, sizeof(sockaddr_in));
  if (rc == -1) {
    // TODO: Handle/log error !!!!
    printf("sendto failed, errno %d - %s.\n", errno, strerror(errno));
    return -1;
  }
  else {
    return rc;
  }
}


zSocketBase::SocketError zSocketUDP::impl_create(void) {
  int domain = -1;
  if (_bindAddress->getType() == zSocketAddress::ADDRESS_TYPE_IPv4) {
    domain = AF_INET;
  }
  else if (_bindAddress->getType() == zSocketAddress::ADDRESS_TYPE_IPv6) {
    domain = AF_INET6;
  }
  else {
    return SOCKET_ERROR_INVALID_ADDRESS;
  }

  _desc = socket(domain, SOCK_DGRAM, 0);
  return SOCKET_OK;
}

