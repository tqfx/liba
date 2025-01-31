#[test]
fn regress_linear() {
    let n = 100;
    let mut coef = [0.0];
    let mut regress = liba::regress_linear::new(&mut coef, 0.0);
    let mut out = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0];
    let x = [0.0, 1.0, 2.0, 3.0, 4.0];
    let y = [1.0, 2.0, 3.0, 4.0, 5.0];
    let y_mean = liba::real_mean(&y);
    regress.set_coef(&mut coef);
    regress.coef();

    regress.zero();
    for _ in 0..n {
        regress.sgd(&x, &y, 0.01);
    }
    std::println!("y={}x+{}", coef[0], regress.bias);
    regress.pdm(&x, &mut out, y_mean);
    std::println!("{}", liba::real_sum(&out));
    std::println!("{:?}", out);
    for i in 0..x.len() {
        out[i] = regress.eval(&[x[i]]);
    }
    std::println!("{:?}", out);
    regress.err(&x, &y, &mut out);
    std::println!("{:?}", out);

    regress.zero();
    for _ in 0..n {
        regress.err(&x, &y, &mut out);
        regress.bgd(&x, &out, 0.1);
    }
    std::println!("y={}x+{}", coef[0], regress.bias);
    regress.pdm(&x, &mut out, y_mean);
    std::println!("{}", liba::real_sum(&out));
    for i in 0..x.len() {
        out[i] = regress.eval(&[x[i]]);
    }
    std::println!("{:?}", out);
    regress.err(&x, &y, &mut out);
    std::println!("{:?}", out);

    regress.zero();
    regress.mgd(&x, &y, &mut out, 0.001, 0.2, 0.1, 100, n, 10);
    std::println!("y={}x+{}", coef[0], regress.bias);
    regress.pdm(&x, &mut out, y_mean);
    std::println!("{}", liba::real_sum(&out));
    for i in 0..x.len() {
        out[i] = regress.eval(&[x[i]]);
    }
    std::println!("{:?}", out);
    regress.err(&x, &y, &mut out);
    std::println!("{:?}", out);
}
