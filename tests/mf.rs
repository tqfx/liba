#[cfg(test)]
mod mf {
    #[test]
    fn gauss2() {
        for i in -4..=4 {
            let x = i as liba::real;
            std::println!("{:+} {}", x, liba::mf::gauss2(x, 1.0, -1.0, 1.0, 1.0));
        }
    }
    #[test]
    fn gbell() {
        for i in -4..=4 {
            let x = i as liba::real;
            std::println!("{:+} {}", x, liba::mf::gbell(x, 2.0, 4.0, 0.0));
        }
    }
    #[test]
    fn sig() {
        for i in -4..=4 {
            let x = i as liba::real;
            std::println!("{:+} {}", x, liba::mf::sig(x, 2.0, 0.0));
        }
    }
    #[test]
    fn dsig() {
        for i in -4..=4 {
            let x = i as liba::real;
            std::println!("{:+} {}", x, liba::mf::dsig(x, 5.0, -2.0, 5.0, 2.0));
        }
    }
    #[test]
    fn psig() {
        for i in -4..=4 {
            let x = i as liba::real;
            std::println!("{:+} {}", x, liba::mf::psig(x, 5.0, -2.0, -5.0, 2.0));
        }
    }
    #[test]
    fn trap() {
        for i in -3..=3 {
            let x = i as liba::real;
            std::println!("{:+} {}", x, liba::mf::trap(x, -2.0, -1.0, 1.0, 2.0));
        }
    }
    #[test]
    fn tri() {
        for i in -2..=2 {
            let x = i as liba::real;
            std::println!("{:+} {}", x, liba::mf::tri(x, -1.0, 0.0, 1.0));
        }
    }
    #[test]
    fn lins() {
        for i in -2..=2 {
            let x = i as liba::real;
            std::println!("{:+} {}", x, liba::mf::lins(x, -1.0, 1.0));
        }
    }
    #[test]
    fn linz() {
        for i in -2..=2 {
            let x = i as liba::real;
            std::println!("{:+} {}", x, liba::mf::linz(x, -1.0, 1.0));
        }
    }
    #[test]
    fn s() {
        for i in -2..=2 {
            let x = i as liba::real;
            std::println!("{:+} {}", x, liba::mf::s(x, -1.0, 1.0));
        }
    }
    #[test]
    fn z() {
        for i in -2..=2 {
            let x = i as liba::real;
            std::println!("{:+} {}", x, liba::mf::z(x, -1.0, 1.0));
        }
    }
    #[test]
    fn pi() {
        for i in -3..=3 {
            let x = i as liba::real;
            std::println!("{:+} {}", x, liba::mf::pi(x, -2.0, -1.0, 1.0, 2.0));
        }
    }
}
