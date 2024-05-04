#[test]
fn lpf() {
    let mut lpf = liba::lpf::new(10.0, 0.01);
    lpf.gen(10.0, 0.01).zero().iter(1.0);
}
