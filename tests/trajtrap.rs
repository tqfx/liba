#[test]
fn trajtrap() {
    let x = 0.5;
    {
        let mut a = liba::trajtrap::new();
        std::print!("{} ", a.gen(2.0, 2.0, -2.0, 0.0, 2.0, 0.0, 0.0));
        std::println!("[{}, {}, {}]", a.pos(x), a.vel(x), a.acc(x));
    }
}
