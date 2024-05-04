#[test]
fn crc32() {
    {
        let ctx = liba::crc32::new_msb(0x1EDC6F41);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x512B456E);
    }
    {
        let ctx = liba::crc32::new_lsb(0x04C11DB7);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x450EAFB0);
    }
}
