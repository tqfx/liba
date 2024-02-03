//! Cyclic Redundancy Check

/// Cyclic Redundancy Check for 8 bits
#[repr(C)]
pub struct crc8 {
    /// Cyclic Redundancy Check comparison table
    pub table: [u8; 0x100],
}

extern "C" {
    fn a_crc8m_init(table: *mut u8, poly: u8);
    fn a_crc8l_init(table: *mut u8, poly: u8);
    fn a_crc8(table: *const u8, pdate: *const u8, nbyte: usize, value: u8) -> u8;
}

impl crc8 {
    /// initialize for MSB CRC-8
    #[inline(always)]
    pub fn new_msb(poly: u8) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc8m_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// initialize for LSB CRC-8
    #[inline(always)]
    pub fn new_lsb(poly: u8) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc8l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// generate for MSB CRC-8
    #[inline(always)]
    pub fn gen_msb(&mut self, poly: u8) -> &mut Self {
        unsafe { a_crc8m_init(self.table.as_mut_ptr(), poly) };
        self
    }
    /// generate for LSB CRC-8
    #[inline(always)]
    pub fn gen_lsb(&mut self, poly: u8) -> &mut Self {
        unsafe { a_crc8l_init(self.table.as_mut_ptr(), poly) };
        self
    }
    /// calculate for CRC-8
    #[inline(always)]
    pub fn eval(self, block: &[u8], value: u8) -> u8 {
        unsafe { a_crc8(self.table.as_ptr(), block.as_ptr(), block.len(), value) }
    }
}

#[test]
fn crc8() {
    extern crate std;
    {
        let ctx = crate::crc::crc8::new_msb(0x07);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x45);
    }
    {
        let ctx = crate::crc::crc8::new_lsb(0x31);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x75);
    }
}

/// Cyclic Redundancy Check for 16 bits
#[repr(C)]
pub struct crc16 {
    /// Cyclic Redundancy Check comparison table
    pub table: [u16; 0x100],
    eval: unsafe extern "C" fn(*const u16, *const u8, usize, u16) -> u16,
}

extern "C" {
    fn a_crc16m_init(table: *mut u16, poly: u16);
    fn a_crc16l_init(table: *mut u16, poly: u16);
    fn a_crc16m(table: *const u16, pdate: *const u8, nbyte: usize, value: u16) -> u16;
    fn a_crc16l(table: *const u16, pdate: *const u8, nbyte: usize, value: u16) -> u16;
}

impl crc16 {
    /// initialize for MSB CRC-16
    #[inline(always)]
    pub fn new_msb(poly: u16) -> Self {
        let mut ctx: Self = Self {
            table: [0; 0x100],
            eval: a_crc16m,
        };
        unsafe { a_crc16m_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// initialize for LSB CRC-16
    #[inline(always)]
    pub fn new_lsb(poly: u16) -> Self {
        let mut ctx: Self = Self {
            table: [0; 0x100],
            eval: a_crc16l,
        };
        unsafe { a_crc16l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// generate for MSB CRC-16
    #[inline(always)]
    pub fn gen_msb(&mut self, poly: u16) -> &mut Self {
        unsafe { a_crc16m_init(self.table.as_mut_ptr(), poly) };
        self.eval = a_crc16m;
        self
    }
    /// generate for LSB CRC-16
    #[inline(always)]
    pub fn gen_lsb(&mut self, poly: u16) -> &mut Self {
        unsafe { a_crc16l_init(self.table.as_mut_ptr(), poly) };
        self.eval = a_crc16l;
        self
    }
    /// calculate for CRC-16
    #[inline(always)]
    pub fn eval(self, block: &[u8], value: u16) -> u16 {
        unsafe { (self.eval)(self.table.as_ptr(), block.as_ptr(), block.len(), value) }
    }
}

#[test]
fn crc16() {
    extern crate std;
    {
        let ctx = crate::crc::crc16::new_msb(0x1021);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x9C58);
    }
    {
        let ctx = crate::crc::crc16::new_lsb(0x8005);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x443D);
    }
}

/// Cyclic Redundancy Check for 32 bits
#[repr(C)]
pub struct crc32 {
    /// Cyclic Redundancy Check comparison table
    pub table: [u32; 0x100],
    eval: unsafe extern "C" fn(*const u32, *const u8, usize, u32) -> u32,
}

extern "C" {
    fn a_crc32m_init(table: *mut u32, poly: u32);
    fn a_crc32l_init(table: *mut u32, poly: u32);
    fn a_crc32m(table: *const u32, pdate: *const u8, nbyte: usize, value: u32) -> u32;
    fn a_crc32l(table: *const u32, pdate: *const u8, nbyte: usize, value: u32) -> u32;
}

impl crc32 {
    /// initialize for MSB CRC-32
    #[inline(always)]
    pub fn new_msb(poly: u32) -> Self {
        let mut ctx: Self = Self {
            table: [0; 0x100],
            eval: a_crc32m,
        };
        unsafe { a_crc32m_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// initialize for LSB CRC-32
    #[inline(always)]
    pub fn new_lsb(poly: u32) -> Self {
        let mut ctx: Self = Self {
            table: [0; 0x100],
            eval: a_crc32l,
        };
        unsafe { a_crc32l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// generate for MSB CRC-32
    #[inline(always)]
    pub fn gen_msb(&mut self, poly: u32) -> &mut Self {
        unsafe { a_crc32m_init(self.table.as_mut_ptr(), poly) };
        self.eval = a_crc32m;
        self
    }
    /// generate for LSB CRC-32
    #[inline(always)]
    pub fn gen_lsb(&mut self, poly: u32) -> &mut Self {
        unsafe { a_crc32l_init(self.table.as_mut_ptr(), poly) };
        self.eval = a_crc32l;
        self
    }
    /// calculate for CRC-32
    #[inline(always)]
    pub fn eval(self, block: &[u8], value: u32) -> u32 {
        unsafe { (self.eval)(self.table.as_ptr(), block.as_ptr(), block.len(), value) }
    }
}

#[test]
fn crc32() {
    extern crate std;
    {
        let ctx = crate::crc::crc32::new_msb(0x1EDC6F41);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x512B456E);
    }
    {
        let ctx = crate::crc::crc32::new_lsb(0x04C11DB7);
        assert_eq!(ctx.eval(b"0123456789", 0), 0x450EAFB0);
    }
}

/// Cyclic Redundancy Check for 64 bits
#[repr(C)]
pub struct crc64 {
    /// Cyclic Redundancy Check comparison table
    pub table: [u64; 0x100],
    eval: unsafe extern "C" fn(*const u64, *const u8, usize, u64) -> u64,
}

extern "C" {
    fn a_crc64m_init(table: *mut u64, poly: u64);
    fn a_crc64l_init(table: *mut u64, poly: u64);
    fn a_crc64m(table: *const u64, pdate: *const u8, nbyte: usize, value: u64) -> u64;
    fn a_crc64l(table: *const u64, pdate: *const u8, nbyte: usize, value: u64) -> u64;
}

impl crc64 {
    /// initialize for MSB CRC-64
    #[inline(always)]
    pub fn new_msb(poly: u64) -> Self {
        let mut ctx: Self = Self {
            table: [0; 0x100],
            eval: a_crc64m,
        };
        unsafe { a_crc64m_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// initialize for LSB CRC-64
    #[inline(always)]
    pub fn new_lsb(poly: u64) -> Self {
        let mut ctx: Self = Self {
            table: [0; 0x100],
            eval: a_crc64l,
        };
        unsafe { a_crc64l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// generate for MSB CRC-64
    #[inline(always)]
    pub fn gen_msb(&mut self, poly: u64) -> &mut Self {
        unsafe { a_crc64m_init(self.table.as_mut_ptr(), poly) };
        self.eval = a_crc64m;
        self
    }
    /// generate for LSB CRC-64
    #[inline(always)]
    pub fn gen_lsb(&mut self, poly: u64) -> &mut Self {
        unsafe { a_crc64l_init(self.table.as_mut_ptr(), poly) };
        self.eval = a_crc64l;
        self
    }
    /// calculate for CRC-64
    #[inline(always)]
    pub fn eval(self, block: &[u8], value: u64) -> u64 {
        unsafe { (self.eval)(self.table.as_ptr(), block.as_ptr(), block.len(), value) }
    }
}

#[test]
fn crc64() {
    extern crate std;
    {
        let ctx = crate::crc::crc64::new_msb(0x000000000000001B);
        assert_eq!(ctx.eval(b"0123456789", 0), 0xE4FFBEA588AFC790);
    }
    {
        let ctx = crate::crc::crc64::new_lsb(0x42F0E1EBA9EA3693);
        assert_eq!(ctx.eval(b"0123456789", 0), 0xDA60676A5CDE0008);
    }
}
