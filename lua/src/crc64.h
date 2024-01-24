/***
 64-bit Cyclic Redundancy Check
 @classmod a.crc64
*/

#ifndef LUA_LIBA_CRC64_H
#define LUA_LIBA_CRC64_H

#include "a.h"

/***
 64-bit Cyclic Redundancy Check
 @field table Cyclic Redundancy Check comparison table
 @table a.crc64
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for 64-bit Cyclic Redundancy Check
 @tparam integer poly polynomial that is CRC's divisor
 @tparam boolean reversed whether or not to reverse
 @treturn a.crc64 64-bit Cyclic Redundancy Check userdata
 @function new
*/
int liba_crc64_new(lua_State *L);

/***
 generate for 64-bit Cyclic Redundancy Check
 @tparam integer poly polynomial that is CRC's divisor
 @tparam boolean reversed whether or not to reverse
 @treturn a.crc64 64-bit Cyclic Redundancy Check userdata
 @function gen
*/
int liba_crc64_gen(lua_State *L);

/***
 calculate for 64-bit Cyclic Redundancy Check
 @tparam string block block to be processed
 @tparam integer value initial value
 @treturn integer output value
 @function eval
*/
int liba_crc64_eval(lua_State *L);

/***
 pack a block and its 64-bit Cyclic Redundancy Check value
 @tparam string block block to be processed
 @tparam integer value initial value
 @treturn string packed block
 @function pack
*/
int liba_crc64_pack(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* crc64.h */
