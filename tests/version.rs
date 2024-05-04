#[test]
fn version() {
    std::println!("{}", liba::version::check(0, 0, 0));
    std::println!("major {}", liba::version::major());
    std::println!("minor {}", liba::version::minor());
    std::println!("patch {}", liba::version::patch());
    std::println!("tweak {}", liba::version::tweak());
    let v000 = liba::version::new(0, 0, 0);
    let mut v001 = liba::version::new(0, 0, 0);
    let mut ver = [0u8; 48];
    v001.parse("0.0.1-a.1");
    v001.tostr(&mut ver);
    std::println!("{}", std::str::from_utf8(&ver).unwrap());
    assert!(v001 > v000);
    assert!(v000 < v001);
    assert!(v000 >= v000);
    assert!(v000 <= v000);
    assert!(v000 == v000);
    assert!(v000 != v001);
}
