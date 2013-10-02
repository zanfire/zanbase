/******************************************************************************
 * Copyright 2011 Matteo Valdina
 *      
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *      
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef ZSOCKETADDRESSIPv4_H__
#define ZSOCKETADDRESSIPv4_H__

#include "zSocketAddress.h"

#if HAVE_SYS_TYPES_H
#  include <sys/types.h>
#endif
#if HAVE_SYS_SOCKET_H
#  include <sys/socket.h>
#endif
#if HAVE_NETINET_IN_H
#  include <netinet/in.h>
#endif

class zSocketAddressIPv4 : public zSocketAddress {
protected:
  sockaddr_in _sockaddr;


public:
  zSocketAddressIPv4(char const* address, uint16_t port);
  zSocketAddressIPv4(uint32_t address, uint16_t port);
  zSocketAddressIPv4(sockaddr_in const& addr);

  virtual ~zSocketAddressIPv4(void);

  virtual zSocketAddress* clone(void) const;

  virtual sockaddr* get_socket_addr(void) const;
  virtual int get_socket_addr_len(void) const { return sizeof(_sockaddr); }

  virtual zString get_address_as_string(void) const;

  uint32_t get_address(void);
  uint16_t get_port(void);
};


#endif // SOCKETADDRESSIPv4_H__
