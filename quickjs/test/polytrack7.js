import * as a from "liba.so";
var polytrack7 = new a.polytrack7(0, 1, 0, 0)
polytrack7.gen(0, 10, 0, 10, 0, 0)
for (var i = 0; i < 10; i += 0.1) {
    console.log(i, polytrack7.pos(i), polytrack7.vel(i), polytrack7.acc(i), polytrack7.jer(0.5))
}
