#[test]
fn crc16() {
    {
        let ctx = liba::crc16::new_msb(0x1021);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x9C58);
    }
    {
        let ctx = liba::crc16::new_lsb(0x8005);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x443D);
    }
}
