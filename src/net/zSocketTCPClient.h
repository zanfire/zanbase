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

#ifndef ZSOCKETTCPCLIENT_H__
#define ZSOCKETTCPCLIENT_H__

#include "zObject.h"
#include "zSocketTCP.h"


#if HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif

class zSocketAddress;

class zSocketTCPClient : public zSocketTCP {
protected:
  zSocketAddress* _remoteAddress;
public:
  zSocketTCPClient(SOCKET_DESC desc, zSocketAddress* localAddress, sockaddr const& fromAddr, int fromAddrLen);
  virtual ~zSocketTCPClient(void);
};

#endif // ZSOCKETTCPCLIENT_H__
