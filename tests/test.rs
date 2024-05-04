#[test]
fn usqrt() {
    std::println!("{}", liba::u32_sqrt(u32::MAX));
    std::println!("{}", liba::u64_sqrt(u64::MAX));
}

#[test]
fn rsqrt() {
    std::println!("1/sqrt({})={}", 4, liba::f32_rsqrt(4.0));
    std::println!("1/sqrt({})={}", 4, liba::f64_rsqrt(4.0));
}

#[test]
fn hash() {
    let text: [u8; 10] = *b"0123456789";
    std::println!("{}", liba::hash_bkdr(&text, 0));
    std::println!("{}", liba::hash_sdbm(&text, 0));
}
