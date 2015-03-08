/******************************************************************************
  Copyright (c) 2014 Ryan Juckett
  http://www.ryanjuckett.com/

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.

  3. This notice may not be removed or altered from any source
     distribution.
******************************************************************************/

#ifndef RJ__Standard_h
#define RJ__Standard_h

// NOTICE: Inserted
/**
 * @file  standard.h
 * @brief Type defitions for the Dragon4 library
 *
 */

// NOTICE: Changed
#ifndef AMIGA
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#endif

#ifdef AOS
#include <stddef.h>
#include <sys/types.h>
typedef u_int8_t    uint8_t;
typedef u_int16_t   uint16_t;
typedef u_int32_t   uint32_t;
typedef u_int64_t   uint64_t;
#endif

#ifdef AOS4
#error Includedes must be defined for Amiga OS 4+
#endif

#ifdef AROS
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#endif

// NOTICE: Changed
#define RJ_ASSERT(condition)

// Boolean types
typedef bool        tB;

// Character types
typedef char        tC8;

// Unsigned integer types
typedef uint8_t     tU8;
typedef uint16_t    tU16;
typedef uint32_t    tU32;
typedef uint64_t    tU64;

// Signed integer types
typedef int8_t      tS8;
typedef int16_t     tS16;
typedef int32_t     tS32;
typedef int64_t     tS64;

// Floating point types
typedef float       tF32;
typedef double      tF64;

// Size types
typedef size_t      tSize;
typedef ptrdiff_t   tPtrDiff;

#endif
