import * as a from "liba.so";
var polytrack5 = new a.polytrack5(0, 1, 0, 1)
polytrack5.gen(0, 10, 0, 10, 0, 0)
for (var i = 0; i < 10; i += 0.1) {
    console.log(i, polytrack5.pos(i), polytrack5.vel(i), polytrack5.acc(i))
}
