/**
 * @file cpu_endian.c
 * @brief Byte order conversion
 *
 * @section License
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2010-2019 Oryx Embedded SARL. All rights reserved.
 * Ported by ACP Aviation
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.9.6
 **/

//Dependencies
#include <stdint.h>
#include "cpu_endian.h"
#include "cpu_endian_defs.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

uint16_t swapInt16func(uint16_t value);                                         //Byte order conversion functions
uint32_t swapInt32func(uint32_t value);
uint64_t swapInt64func(uint64_t value);

uint8_t reverseInt4(uint8_t value);                                             //Bit reversal functions
uint8_t reverseInt8(uint8_t value);
uint16_t reverseInt16(uint16_t value);
uint32_t reverseInt32(uint32_t value);
uint64_t reverseInt64(uint64_t value);

/**
 * @brief Reverse the byte order of a 16-bit word
 * @param[in] value 16-bit value
 * @return 16-bit value with byte order swapped
 **/
uint16_t swapInt16func(uint16_t value)
{
   return SWAPINT16(value);
}

/**
 * @brief Reverse the byte order of a 32-bit word
 * @param[in] value 32-bit value
 * @return 32-bit value with byte order swapped
 **/
uint32_t swapInt32func(uint32_t value)
{
   return SWAPINT32(value);
}

/**
 * @brief Reverse the byte order of a 64-bit word
 * @param[in] value 64-bit value
 * @return 64-bit value with byte order swapped
 **/
uint64_t swapInt64func(uint64_t value)
{
   return SWAPINT64(value);
}

/**
 * @brief Reverse bit order in a 4-bit word
 * @param[in] value 4-bit value
 * @return 4-bit value with bit order reversed
 **/
uint8_t reverseInt4(uint8_t value)
{
   value = ((value & 0x0Cu) >> 2u) | ((value & 0x03u) << 2u);
   value = ((value & 0x0Au) >> 1u) | ((value & 0x05u) << 1u);

   return value;
}

/**
 * @brief Reverse bit order in a byte
 * @param[in] value 8-bit value
 * @return 8-bit value with bit order reversed
 **/
uint8_t reverseInt8(uint8_t value)
{
   value = ((value & 0xF0u) >> 4u) | ((value & 0x0Fu) << 4u);
   value = ((value & 0xCCu) >> 2u) | ((value & 0x33u) << 2u);
   value = ((value & 0xAAu) >> 1u) | ((value & 0x55u) << 1u);

   return value;
}

/**
 * @brief Reverse bit order in a 16-bit word
 * @param[in] value 16-bit value
 * @return 16-bit value with bit order reversed
 **/
uint16_t reverseInt16(uint16_t value)
{
   value = ((value & 0xFF00u) >> 8u) | ((value & 0x00FFu) << 8u);
   value = ((value & 0xF0F0u) >> 4u) | ((value & 0x0F0Fu) << 4u);
   value = ((value & 0xCCCCu) >> 2u) | ((value & 0x3333u) << 2u);
   value = ((value & 0xAAAAu) >> 1u) | ((value & 0x5555u) << 1u);

   return value;
}

/**
 * @brief Reverse bit order in a 32-bit word
 * @param[in] value 32-bit value
 * @return 32-bit value with bit order reversed
 **/
uint32_t reverseInt32(uint32_t value)
{
   value = ((value & 0xFFFF0000UL) >> 16ul) | ((value & 0x0000FFFFUL) << 16ul);
   value = ((value & 0xFF00FF00UL) >> 8ul) | ((value & 0x00FF00FFUL) << 8ul);
   value = ((value & 0xF0F0F0F0UL) >> 4ul) | ((value & 0x0F0F0F0FUL) << 4ul);
   value = ((value & 0xCCCCCCCCUL) >> 2ul) | ((value & 0x33333333UL) << 2ul);
   value = ((value & 0xAAAAAAAAUL) >> 1ul) | ((value & 0x55555555UL) << 1ul);

   return value;
}

/**
 * @brief Reverse bit order in a 64-bit word
 * @param[in] value 64-bit value
 * @return 64-bit value with bit order reversed
 **/
uint64_t reverseInt64(uint64_t value)
{
   value = ((value & 0xFFFFFFFF00000000ULL) >> 32ull) | ((value & 0x00000000FFFFFFFFULL) << 32ull);
   value = ((value & 0xFFFF0000FFFF0000ULL) >> 16ull) | ((value & 0x0000FFFF0000FFFFULL) << 16ull);
   value = ((value & 0xFF00FF00FF00FF00ULL) >> 8ull) | ((value & 0x00FF00FF00FF00FFULL) << 8ull);
   value = ((value & 0xF0F0F0F0F0F0F0F0ULL) >> 4ull) | ((value & 0x0F0F0F0F0F0F0F0FULL) << 4ull);
   value = ((value & 0xCCCCCCCCCCCCCCCCULL) >> 2ull) | ((value & 0x3333333333333333ULL) << 2ull);
   value = ((value & 0xAAAAAAAAAAAAAAAAULL) >> 1ull) | ((value & 0x5555555555555555ULL) << 1ull);

   return value;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
