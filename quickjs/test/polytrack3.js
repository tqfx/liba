import * as a from "liba.so";
var polytrack3 = new a.polytrack3(0, 1, 0, 1)
polytrack3.gen(0, 10, 0, 10, 0, 0)
for (var i = 0; i < 10; i += 0.1) {
    console.log(i, polytrack3.pos(i), polytrack3.vel(i), polytrack3.acc(i))
}
