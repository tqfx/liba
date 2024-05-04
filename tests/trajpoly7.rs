#[test]
fn trajpoly7() {
    let x = 0.5;
    {
        let mut traj = liba::trajpoly7::new(1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
        std::println!(
            "[{}, {}, {}, {}]",
            traj.pos(x),
            traj.vel(x),
            traj.acc(x),
            traj.jer(x)
        );
    }
}
