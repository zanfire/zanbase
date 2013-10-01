/******************************************************************************
 * Copyright 2013 Matteo Valdina
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

#ifndef ZSENDER_H__
#define ZSENDER_H__

#include "zObject.h"
#include "zRunnable.h"

class zMutex;
class zSocketUDP;
class zThread;

#define ZSENDER_CHUNKS_COUNT  50 //1000 * 64

class zSender : public zRunnable {
protected:
  struct Entry {
    unsigned char buffer[2 * 1024];
    int lenght;
    unsigned int ip;
    int port;
    zSocketUDP* socket;
    unsigned int send_time_ms;
    
    Entry* prev;
    Entry* next;
  };


  zMutex* _mtx_used;
  zMutex* _mtx_free;

  int _count_used;
  int _count_free;
  Entry* _head_used;
  Entry* _tail_used;
  Entry* _head_free;
  Entry* _tail_free;
  Entry _chunks[ZSENDER_CHUNKS_COUNT];

  zThread* _thread;
  bool _must_continue;

  unsigned int _stat_num_processed_ok;
  unsigned int _stat_num_processed_failed;

public:
  zSender(void);
  virtual ~zSender(void);

  void start(void);

  /// Send a packet to the destination.
  void send(zSocketUDP* sock, unsigned int ip, int port, unsigned char* buffer, int size, int delay_ms);

protected:
  /// zRunnable impl.
  virtual int run(void* arg);
  
  /// Move a entry from used list to the free list.
  void move_to_free(Entry* entry);
  /// Add a entry in the used list.
  void add_to_used(Entry* entry);
  void add_to_free(Entry* entry); 

   Entry* remove_from_used(void);
  /// Get and remove an entry from the free list.
  Entry* remove_from_free(void);

  static void print_list(Entry* entry);
};

#endif // ZSENDER_H__
