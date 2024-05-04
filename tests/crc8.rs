#[test]
fn crc8() {
    {
        let ctx = liba::crc8::new_msb(0x07);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x45);
    }
    {
        let ctx = liba::crc8::new_lsb(0x31);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x75);
    }
}
