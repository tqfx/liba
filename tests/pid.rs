#[test]
fn pid() {
    let mut pid = liba::pid::new();
    pid.kpid(10.0, 0.1, 1.0);
    std::println!("{}", pid.zero().pos(1.0, 0.0));
    std::println!("{}", pid.zero().inc(1.0, 0.0));
}
