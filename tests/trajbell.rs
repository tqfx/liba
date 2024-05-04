#[test]
fn trajbell() {
    let x = 0.5;
    {
        let mut traj = liba::trajbell::new();
        std::print!("{} ", traj.gen(3.0, 2.0, 3.0, 0.0, 10.0, 0.0, 0.0));
        std::println!(
            "[{}, {}, {}, {}]",
            traj.pos(x),
            traj.vel(x),
            traj.acc(x),
            traj.jer(x)
        );
    }
}
