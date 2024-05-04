#[test]
fn tf() {
    let num = [6.59492796e-05, 6.54019884e-05];
    let den = [-1.97530991, 0.97530991];
    let mut input = [0.0; 2];
    let mut output = [0.0; 2];
    let mut tf = liba::tf::new(&num, &mut input, &den, &mut output);
    tf.set_num(&num, &mut input).set_den(&den, &mut output);
    std::println!("{} {}", tf.iter(10.0), tf.iter(10.0));
    std::println!("{:?} {:?}", tf.num(), tf.input());
    std::println!("{:?} {:?}", tf.den(), tf.output());
    tf.zero();
}
