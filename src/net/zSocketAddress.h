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

#ifndef ZSOCKETADDRESS_H__
#define ZSOCKETADDRESS_H__

#include "zCommon.h"
#include "zString.h"

#if HAVE_INTTYPES_H
  #include <inttypes.h>
#endif

struct sockaddr;

/**
 * Abstract definition of a socket address.
 */
class zSocketAddress {
public:
  enum AddressType {
    ADDRESS_TYPE_IPv4,
    ADDRESS_TYPE_IPv6
  };

protected:
  AddressType _type;

public:
  zSocketAddress(AddressType type);
  virtual ~zSocketAddress(void);

  AddressType get_type(void) { return _type; }

  virtual sockaddr* get_socket_addr(void) const = 0;
  virtual int get_socket_addr_len(void) const = 0;

  virtual zSocketAddress* clone(void) const = 0;
  virtual zString get_address_as_string(void) const = 0;

  ///
  /// Factory methods
  ///

  static zSocketAddress* create_socket_address_from_string(zString const& str, int port);
};


#endif // ZSOCKETADDRESS_H__
