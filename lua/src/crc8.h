/***
 8-bit Cyclic Redundancy Check
 @classmod a.crc8
*/

#ifndef LUA_LIBA_CRC8_H
#define LUA_LIBA_CRC8_H

#include "a.h"

/***
 8-bit Cyclic Redundancy Check
 @field table Cyclic Redundancy Check comparison table
 @table a.crc8
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for 8-bit Cyclic Redundancy Check
 @tparam integer poly polynomial that is CRC's divisor
 @tparam boolean reversed whether or not to reverse
 @treturn a.crc8 8-bit Cyclic Redundancy Check userdata
 @function new
*/
int liba_crc8_new(lua_State *L);

/***
 generate for 8-bit Cyclic Redundancy Check
 @tparam integer poly polynomial that is CRC's divisor
 @tparam boolean reversed whether or not to reverse
 @treturn a.crc8 8-bit Cyclic Redundancy Check userdata
 @function gen
*/
int liba_crc8_gen(lua_State *L);

/***
 calculate for 8-bit Cyclic Redundancy Check
 @tparam string block block to be processed
 @tparam integer value initial value
 @treturn integer output value
 @function eval
*/
int liba_crc8_eval(lua_State *L);

/***
 pack a block and its 8-bit Cyclic Redundancy Check value
 @tparam string block block to be processed
 @tparam integer value initial value
 @treturn string packed block
 @function pack
*/
int liba_crc8_pack(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* crc8.h */
