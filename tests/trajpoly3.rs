#[test]
fn trajpoly3() {
    let x = 0.5;
    {
        let traj = liba::trajpoly3::new(1.0, 0.0, 1.0, 0.0, 1.0);
        std::println!("[{}, {}, {}]", traj.pos(x), traj.vel(x), traj.acc(x));
    }
}
