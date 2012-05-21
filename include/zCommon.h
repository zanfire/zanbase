/******************************************************************************
 * Copyright 2009-2012 Matteo Valdina
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

#ifndef ZCOMMON_H__
#define ZCOMMON_H__

/// Include configuration of configure script.
#include "config.h"

// NULL define
#if !defined(NULL)
  #define NULL 0
#endif

// Include for intrinsic
#if defined(_WIN32)
  #include <intrin.h>
#else // Add GCC include
#endif

// Define base type for atomic increment and decrement.
#if defined(_WIN32)
  typedef long zref_t;
#else
  typedef long zref_t;
#endif

// Define increment and decrement
#if defined(_WIN32)
  #pragma intrinsic (_InterlockedIncrement)
  #pragma intrinsic (_InterlockedDecrement)
  #define ATOMIC_INC(X) _InterlockedIncrement(&X)
  #define ATOMIC_DEC(X) _InterlockedDecrement(&X)
#else
  #define ATOMIC_INC(X) __sync_fetch_and_add(&X, 1)
  #define ATOMIC_DEC(X) __sync_fetch_and_sub(&X, 1)
#endif


/// Include standard uint32_t, uint16_t, etc

#if HAVE_INTTYPES_H
#  include <inttypes.h>
#elif defined(_WIN32)
#  include <stdint.h>
#else
// Unimplemented
#endif

/// Enum that provides a specific text for thread safe values instead of a boolean.
enum IsThreadSafe {
  YES,
  NO
};

#endif // ZCOMMON_H__

