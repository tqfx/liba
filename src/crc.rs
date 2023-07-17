//! Cyclic Redundancy Check

/// polynomial value for 8 bits Cyclic Redundancy Check
pub const POLY8: u8 = 0x31;
/// initialize value for 8 bits Cyclic Redundancy Check
pub const INIT8: u8 = 0x00;
/// Cyclic Redundancy Check for 8 bits
#[repr(C)]
pub struct crc8 {
    /// Cyclic Redundancy Check comparison table
    table: [u8; 0x100],
}

extern "C" {
    fn a_crc8l_init(table: *mut u8, poly: u8);
    fn a_crc8h_init(table: *mut u8, poly: u8);
    fn a_crc8(table: *const u8, pdate: *const u8, nbyte: usize, value: u8) -> u8;
}

impl crc8 {
    /// initialize function for low 8 bits Cyclic Redundancy Check
    pub fn new_low(poly: u8) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc8l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculation function for low 8 bits Cyclic Redundancy Check
    pub fn low(self, data: &[u8], value: u8) -> u8 {
        unsafe { a_crc8(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }

    /// initialize function for high 8 bits Cyclic Redundancy Check
    pub fn new_high(poly: u8) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc8h_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculation function for high 8 bits Cyclic Redundancy Check
    pub fn high(self, data: &[u8], value: u8) -> u8 {
        unsafe { a_crc8(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
}

#[test]
fn crc8() {
    {
        let ctx = crate::crc::crc8::new_low(POLY8);
        ctx.low(b"", INIT8);
    }
    {
        let ctx = crate::crc::crc8::new_high(POLY8);
        ctx.high(b"", INIT8);
    }
}

/// polynomial value for 16 bits Cyclic Redundancy Check
pub const POLY16: u16 = 0xA001;
/// initialize value for 16 bits Cyclic Redundancy Check
pub const INIT16: u16 = 0x0000;
/// Cyclic Redundancy Check for 16 bits
#[repr(C)]
pub struct crc16 {
    /// Cyclic Redundancy Check comparison table
    table: [u16; 0x100],
}

extern "C" {
    fn a_crc16l_init(table: *mut u16, poly: u16);
    fn a_crc16h_init(table: *mut u16, poly: u16);
    fn a_crc16l(table: *const u16, pdate: *const u8, nbyte: usize, value: u16) -> u16;
    fn a_crc16h(table: *const u16, pdate: *const u8, nbyte: usize, value: u16) -> u16;
}

impl crc16 {
    /// initialize function for low 16 bits Cyclic Redundancy Check
    pub fn new_low(poly: u16) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc16l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculation function for low 16 bits Cyclic Redundancy Check
    pub fn low(self, data: &[u8], value: u16) -> u16 {
        unsafe { a_crc16l(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }

    /// initialize function for high 16 bits Cyclic Redundancy Check
    pub fn new_high(poly: u16) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc16h_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculation function for high 16 bits Cyclic Redundancy Check
    pub fn high(self, data: &[u8], value: u16) -> u16 {
        unsafe { a_crc16h(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
}

#[test]
fn crc16() {
    {
        let ctx = crate::crc::crc16::new_low(POLY16);
        ctx.low(b"", INIT16);
    }
    {
        let ctx = crate::crc::crc16::new_high(POLY16);
        ctx.high(b"", INIT16);
    }
}

/// polynomial value for 32 bits Cyclic Redundancy Check
pub const POLY32: u32 = 0xEDB88320;
/// initialize value for 32 bits Cyclic Redundancy Check
pub const INIT32: u32 = 0xFFFFFFFF;
/// Cyclic Redundancy Check for 32 bits
#[repr(C)]
pub struct crc32 {
    /// Cyclic Redundancy Check comparison table
    table: [u32; 0x100],
}

extern "C" {
    fn a_crc32l_init(table: *mut u32, poly: u32);
    fn a_crc32h_init(table: *mut u32, poly: u32);
    fn a_crc32l(table: *const u32, pdate: *const u8, nbyte: usize, value: u32) -> u32;
    fn a_crc32h(table: *const u32, pdate: *const u8, nbyte: usize, value: u32) -> u32;
}

impl crc32 {
    /// initialize function for low 32 bits Cyclic Redundancy Check
    pub fn new_low(poly: u32) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc32l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculation function for low 32 bits Cyclic Redundancy Check
    pub fn low(self, data: &[u8], value: u32) -> u32 {
        unsafe { a_crc32l(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }

    /// initialize function for high 32 bits Cyclic Redundancy Check
    pub fn new_high(poly: u32) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc32h_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculation function for high 32 bits Cyclic Redundancy Check
    pub fn high(self, data: &[u8], value: u32) -> u32 {
        unsafe { a_crc32h(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
}

#[test]
fn crc32() {
    {
        let ctx = crate::crc::crc32::new_low(POLY32);
        ctx.low(b"", INIT32);
    }
    {
        let ctx = crate::crc::crc32::new_high(POLY32);
        ctx.high(b"", INIT32);
    }
}

/// polynomial value for 64 bits Cyclic Redundancy Check
pub const POLY64: u64 = 0x42F0E1EBA9EA3693;
/// initialize value for 64 bits Cyclic Redundancy Check
pub const INIT64: u64 = 0xFFFFFFFFFFFFFFFF;
/// Cyclic Redundancy Check for 64 bits
#[repr(C)]
pub struct crc64 {
    /// Cyclic Redundancy Check comparison table
    table: [u64; 0x100],
}

extern "C" {
    fn a_crc64l_init(table: *mut u64, poly: u64);
    fn a_crc64h_init(table: *mut u64, poly: u64);
    fn a_crc64l(table: *const u64, pdate: *const u8, nbyte: usize, value: u64) -> u64;
    fn a_crc64h(table: *const u64, pdate: *const u8, nbyte: usize, value: u64) -> u64;
}

impl crc64 {
    /// initialize function for low 64 bits Cyclic Redundancy Check
    pub fn new_low(poly: u64) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc64l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculation function for low 64 bits Cyclic Redundancy Check
    pub fn low(self, data: &[u8], value: u64) -> u64 {
        unsafe { a_crc64l(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }

    /// initialize function for high 64 bits Cyclic Redundancy Check
    pub fn new_high(poly: u64) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc64h_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculation function for high 64 bits Cyclic Redundancy Check
    pub fn high(self, data: &[u8], value: u64) -> u64 {
        unsafe { a_crc64h(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
}

#[test]
fn crc64() {
    {
        let ctx = crate::crc::crc64::new_low(POLY64);
        ctx.low(b"", INIT64);
    }
    {
        let ctx = crate::crc::crc64::new_high(POLY64);
        ctx.high(b"", INIT64);
    }
}
