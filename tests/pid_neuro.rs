#[test]
fn pid_neuro() {
    let mut pid = liba::pid_neuro::new();
    pid.kpid(10.0, 1.0, 0.1, 1.0).wpid(1.0, 0.0, 0.0);
    std::println!("{}", pid.inc(1.0, 0.0));
    pid.zero();
}
