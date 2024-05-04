#[test]
fn hpf() {
    let mut hpf = liba::hpf::new(10.0, 0.01);
    hpf.gen(10.0, 0.01).zero().iter(1.0);
}
