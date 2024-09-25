#[test]
fn regress_simple() {
    let mut regress = liba::regress_simple::new(0.0, 0.0);
    let x = [0.0, 2.0, 4.0, 6.0, 8.0];
    let y = [1.0, 2.0, 3.0, 4.0, 5.0];
    regress.ols(&x, &y);
    std::println!("y={}x+{}", regress.coef, regress.bias);
    for i in 0..x.len() {
        std::println!("{},{}", regress.evar(y[i]), regress.eval(x[i]));
    }
    regress.zero();
}
