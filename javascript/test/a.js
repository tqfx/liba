#!/usr/bin/env node
const liba = require("../liba");
console.log(liba.isqrt(4));
console.log(liba.rsqrt(4));
console.log(liba.hash_bkdr("0123456789", 0));
console.log(liba.hash_sdbm("0123456789", 0));
