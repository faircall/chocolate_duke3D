//
//  global.h
//  Duke3D
//
//  Created by fabien sanglard on 12-12-17.
//  Copyright (c) 2012 fabien sanglard. All rights reserved.
//

#ifndef Duke3D_global_h
#define Duke3D_global_h

void FixFilePath(char  *filename);
int FindDistance3D(int ix, int iy, int iz);
void Shutdown(void);

#ifdef _WIN32
#   include "../../Engine/src/windows/inttypes.h"
#else
#   include <stdint.h>
#   include <inttypes.h>
#endif

#ifndef LITTLE_ENDIAN
    #ifdef __APPLE__
    #else
        #define LITTLE_ENDIAN 1234
    #endif
#endif

#ifndef BIG_ENDIAN
     #ifdef __APPLE__
     #else
        #define BIG_ENDIAN 4321
    #endif
#endif

#if PLATFORM_WIN32
#ifndef BYTE_ORDER
#define BYTE_ORDER LITTLE_ENDIAN
#endif
#endif

#ifdef __APPLE__
#if __powerpc__
#define BYTE_ORDER BIG_ENDIAN
#else
// Defined in endian.h
// #define BYTE_ORDER LITTLE_ENDIAN
#endif
#endif

#ifndef BYTE_ORDER
#error Please define your platform.
#endif

#if (BYTE_ORDER == LITTLE_ENDIAN)
#define KeepShort IntelShort
#define SwapShort MotoShort
#define Keepint32_t IntelLong
#define Swapint32_t MotoLong
#else
#define KeepShort MotoShort
#define SwapShort IntelShort
#define Keepint32_t MotoLong
#define Swapint32_t IntelLong
#endif

// ---- Inline endian shims ----
#if defined(_MSC_VER)
#  include <intrin.h>
#  pragma intrinsic(_byteswap_ushort, _byteswap_ulong)
#endif

static inline int16_t IntelShort(int16_t x);
//static inline int32_t IntelLong (int32_t  x);

static inline int16_t MotoShort(int16_t x); 

static inline int32_t MotoLong(int32_t x);

// Map the project’s macros to the helpers above.
#if (BYTE_ORDER == LITTLE_ENDIAN)
#  define KeepShort    IntelShort
#  define SwapShort    MotoShort
#  define Keepint32_t  IntelLong   /* keeping original macro names */
#  define Swapint32_t  MotoLong
#else
#  define KeepShort    MotoShort
#  define SwapShort    IntelShort
#  define Keepint32_t  MotoLong
#  define Swapint32_t  IntelLong
#endif

// (Optional) saner aliases — won’t break existing code.
#ifndef KeepLong
#  define KeepLong IntelLong
#endif
#ifndef SwapLong
#  define SwapLong MotoLong
#endif

// int32_t MotoLong (int32_t l);
// int32_t IntelLong (int32_t l);

void Error (int errorType, char  *error, ...);

#endif
