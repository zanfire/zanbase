#include "zSender.h"

#include "zMutex.h"
#include "zScopeMutex.h"
#include "zTime.h"
#include "zThread.h"
#include "zSocketUDP.h"

#include <string.h>
#include <stdlib.h>

#include <stdio.h>


zSender::zSender(void) {
  _mtx_used = new zMutex();
  _mtx_free = new zMutex();
  _head_used = NULL;
  _tail_used = NULL;
  _head_free = NULL;
  _tail_free = NULL;

  _count_used = 0;
  _count_free = 0;
  // Build the free list.
  memset(&_chunks, 0x00, sizeof(_chunks));
  for (int i = 0; i < ZSENDER_CHUNKS_COUNT; i++) {
    add_to_free(&_chunks[i]);
  }
  
  _must_continue = true;
  _thread = new zThread(this);

  _stat_num_processed_ok = 0;
  _stat_num_processed_failed = 0;

  printf("Count free %d\n", _count_free);
  print_list(_head_free);
}


zSender::~zSender(void) {
  _must_continue = false;
  _thread->join();
  delete _thread;
  delete _mtx_used;
  delete _mtx_free;
}


void zSender::start(void) {
  _thread->start();
}


void zSender::send(zSocketUDP* sock, unsigned int ip, int port, unsigned char* buffer, int size, int delay_ms) {
  Entry* entry = remove_from_free();

  if (entry == NULL) {
//    printf("Fail ...\n");
    return;
  }
  
  memcpy(&(entry->buffer), buffer, size);
  entry->lenght = size;
  entry->socket = sock;
  entry->ip = ip;
  entry->port = port;
  entry->send_time_ms = zTime::current_millis() + delay_ms;

  add_to_used(entry);
}


int zSender::run(void* arg) {
  unsigned int now = 0;
  unsigned int last_perf_log = 0;
  unsigned int prev_processed_ok = 0;
  unsigned int prev_processed_failed = 0;

  while (_must_continue) {
    now = zTime::current_millis();
    Entry* current = _head_used;

    while (current != NULL) {
      Entry* next = current->next;

      if (zTime::current_millis() >= current->send_time_ms) {
        int rc = current->socket->writeBytes(&(current->buffer[0]), current->lenght, current->ip, current->port);

        if (rc >= 0) {
          _stat_num_processed_ok++;
          
          move_to_free(current);
        }
        else {
          _stat_num_processed_failed++;
        }
      }
      // Update list.
      current = next;

      if (now - last_perf_log > 1000) {
        printf("%010d s: Stats %d unproc list  %d proc/s ok %d proc/s failed.\n", (int)(now / 1000), _count_used, (int)(_stat_num_processed_ok - prev_processed_ok), (int)(_stat_num_processed_failed - prev_processed_failed));
        last_perf_log = now;
        prev_processed_ok = _stat_num_processed_ok;
        prev_processed_failed = _stat_num_processed_failed;
      }

      if (_count_used < 0) {
        print_list(_head_used);
        abort();
      }
    }
    zThread::sleep(0); // Use an event.
  }
  return 0;
}


void zSender::move_to_free(zSender::Entry* entry) {
  {
    zScopeMutex scope(_mtx_used);

    /// Remove this entry from used list.
    Entry* prev = entry->prev;
    Entry* next = entry->next;
    if (prev != NULL) {
      prev->next = next;
    }
    else { // Move head
      _head_used = next;
    }
    // Update next link.
    if (next != NULL) {
      next->prev = prev;
    }
    else {
      _tail_used = prev;
    }
    _count_used--;
  }
  entry->prev = NULL;
  entry->next = NULL;

  // Now the entry is orphan, should add this entry at the end of free list.
  add_to_free(entry);
}


void zSender::add_to_used(zSender::Entry* entry) {
  zScopeMutex scope(_mtx_used);

  if (_tail_used == NULL) {
    _tail_used = entry;
    _head_used = entry;
  }
  else {
    _tail_used->next = entry;
    entry->prev = _tail_used;
    _tail_used = entry;
  }
  _count_used++;
}


void zSender::add_to_free(zSender::Entry* entry) {
  zScopeMutex scope(_mtx_free);

  if (_tail_free == NULL) {
    _head_free = entry;
    _tail_free = entry;
  }
  else {
    _tail_free->next = entry;
    entry->prev = _tail_free;
    _tail_free = entry;
  }
  _count_free++;
}


zSender::Entry* zSender::remove_from_free(void) {
  zScopeMutex scope(_mtx_free);
  if (_head_free == NULL) return NULL;

  Entry* entry = _head_free;
  _head_free = _head_free->next;
  entry->next = NULL;
  if (_head_free != NULL) {
    _head_free->prev = NULL;
  }
  else {
    _tail_free = NULL;
  }
  _count_free--;
  return entry;
}


//
// DEBUG stuff.
//
void zSender::print_list(Entry* entry) {
  int count = 0;
  Entry* cur = entry;
  printf("[ ");
  while (cur != NULL && count < ZSENDER_CHUNKS_COUNT * 2) {
    if (cur->next != NULL) {
      printf("%d %p -> ", count, cur);
    }
    else {
      printf("%d %p", count, cur);
    }
    cur = cur->next;
    count++;
  }
  printf("]\n");
}

