/***
 16-bit Cyclic Redundancy Check
 @classmod a.crc16
*/

#ifndef LUA_LIBA_CRC16_H
#define LUA_LIBA_CRC16_H

#include "a.h"

/***
 16-bit Cyclic Redundancy Check
 @field table Cyclic Redundancy Check comparison table
 @table a.crc16
*/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***
 constructor for 16-bit Cyclic Redundancy Check
 @tparam integer poly polynomial that is CRC's divisor
 @tparam boolean reversed whether or not to reverse
 @treturn a.crc16 16-bit Cyclic Redundancy Check userdata
 @function new
*/
int liba_crc16_new(lua_State *L);

/***
 generate for 16-bit Cyclic Redundancy Check
 @tparam integer poly polynomial that is CRC's divisor
 @tparam boolean reversed whether or not to reverse
 @treturn a.crc16 16-bit Cyclic Redundancy Check userdata
 @function gen
*/
int liba_crc16_gen(lua_State *L);

/***
 calculate for 16-bit Cyclic Redundancy Check
 @tparam string block block to be processed
 @tparam integer value initial value
 @treturn integer output value
 @function eval
*/
int liba_crc16_eval(lua_State *L);

/***
 pack a block and its 16-bit Cyclic Redundancy Check value
 @tparam string block block to be processed
 @tparam integer value initial value
 @treturn string packed block
 @function pack
*/
int liba_crc16_pack(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* crc16.h */
