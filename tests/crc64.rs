#[test]
fn crc64() {
    {
        let ctx = liba::crc64::new_msb(0x000000000000001B);
        assert_eq!(ctx.eval(b"0123456789", 0), 0xE4FFBEA588AFC790);
    }
    {
        let ctx = liba::crc64::new_lsb(0x42F0E1EBA9EA3693);
        assert_eq!(ctx.eval(b"0123456789", 0), 0xDA60676A5CDE0008);
    }
}
