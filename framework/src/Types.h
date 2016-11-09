#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef bool                        Boolean;    // 1 bit wide boolean Byte 
typedef uint8_t                     Byte;       // 8 bit wide byte Byte 
typedef uint8_t                     Uint8;      // 8 bit unsigned integer
typedef uint16_t                    Uint16;     // 16 bit unsigned integer
typedef uint32_t                    Uint32;     // 32 bit unsigned integer
typedef uint64_t                    Uint64;     // 64 bit unsigned integer

#ifndef UINT8_MAX
#define UINT8_MAX                  (Uint8) (~((Uint8)  0)) /* 0xFF               */
#endif // UINT8_MAX
#ifndef UINT16_MAX
#define UINT16_MAX                 (Uint16)(~((Uint16) 0)) /* 0xFFFF             */
#endif // UINT16_MAX
#ifndef UINT32_MAX
#define UINT32_MAX                 (Uint32)(~((Uint32) 0)) /* 0xFFFFFFFF         */
#endif // UINT32_MAX
#ifndef UINT64_MAX
#define UINT64_MAX                 (Uint64)(~((Uint64) 0)) /* 0xFFFFFFFFFFFFFFFF */
#endif // UINT64_MAX
#ifndef INT32_MAX
#define INT32_MAX                  (Int32)(0x7fffffff)
#endif // INT32_MAX

#undef True
#define True    true

#undef False
#define False   false

#undef TRUE
#define TRUE    true

#undef FALSE
#define FALSE   false


#endif // TYPES_H
