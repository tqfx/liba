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
    fn a_crc8le_init(table: *mut u8, poly: u8);
    fn a_crc8be_init(table: *mut u8, poly: u8);
    fn a_crc8(table: *const u8, pdate: *const u8, nbyte: usize, value: u8) -> u8;
}

impl crc8 {
    /// initialize for little-endian 8 bits Cyclic Redundancy Check
    pub fn new_le(poly: u8) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc8le_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculate for little-endian 8 bits Cyclic Redundancy Check
    pub fn le(self, data: &[u8], value: u8) -> u8 {
        unsafe { a_crc8(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }

    /// initialize for big-endian 8 bits Cyclic Redundancy Check
    pub fn new_be(poly: u8) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc8be_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculate for big-endian 8 bits Cyclic Redundancy Check
    pub fn be(self, data: &[u8], value: u8) -> u8 {
        unsafe { a_crc8(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
}

#[test]
fn crc8() {
    {
        let ctx = crate::crc::crc8::new_le(POLY8);
        ctx.le(b"", INIT8);
    }
    {
        let ctx = crate::crc::crc8::new_be(POLY8);
        ctx.be(b"", INIT8);
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
    fn a_crc16le_init(table: *mut u16, poly: u16);
    fn a_crc16be_init(table: *mut u16, poly: u16);
    fn a_crc16le(table: *const u16, pdate: *const u8, nbyte: usize, value: u16) -> u16;
    fn a_crc16be(table: *const u16, pdate: *const u8, nbyte: usize, value: u16) -> u16;
}

impl crc16 {
    /// initialize for little-endian 16 bits Cyclic Redundancy Check
    pub fn new_le(poly: u16) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc16le_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculate for little-endian 16 bits Cyclic Redundancy Check
    pub fn le(self, data: &[u8], value: u16) -> u16 {
        unsafe { a_crc16le(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }

    /// initialize for big-endian 16 bits Cyclic Redundancy Check
    pub fn new_be(poly: u16) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc16be_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculate for big-endian 16 bits Cyclic Redundancy Check
    pub fn be(self, data: &[u8], value: u16) -> u16 {
        unsafe { a_crc16be(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
}

#[test]
fn crc16() {
    {
        let ctx = crate::crc::crc16::new_le(POLY16);
        ctx.le(b"", INIT16);
    }
    {
        let ctx = crate::crc::crc16::new_be(POLY16);
        ctx.be(b"", INIT16);
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
    fn a_crc32le_init(table: *mut u32, poly: u32);
    fn a_crc32be_init(table: *mut u32, poly: u32);
    fn a_crc32le(table: *const u32, pdate: *const u8, nbyte: usize, value: u32) -> u32;
    fn a_crc32be(table: *const u32, pdate: *const u8, nbyte: usize, value: u32) -> u32;
}

impl crc32 {
    /// initialize for little-endian 32 bits Cyclic Redundancy Check
    pub fn new_le(poly: u32) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc32le_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculate for little-endian 32 bits Cyclic Redundancy Check
    pub fn le(self, data: &[u8], value: u32) -> u32 {
        unsafe { a_crc32le(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }

    /// initialize for big-endian 32 bits Cyclic Redundancy Check
    pub fn new_be(poly: u32) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc32be_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculate for big-endian 32 bits Cyclic Redundancy Check
    pub fn be(self, data: &[u8], value: u32) -> u32 {
        unsafe { a_crc32be(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
}

#[test]
fn crc32() {
    {
        let ctx = crate::crc::crc32::new_le(POLY32);
        ctx.le(b"", INIT32);
    }
    {
        let ctx = crate::crc::crc32::new_be(POLY32);
        ctx.be(b"", INIT32);
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
    fn a_crc64le_init(table: *mut u64, poly: u64);
    fn a_crc64be_init(table: *mut u64, poly: u64);
    fn a_crc64le(table: *const u64, pdate: *const u8, nbyte: usize, value: u64) -> u64;
    fn a_crc64be(table: *const u64, pdate: *const u8, nbyte: usize, value: u64) -> u64;
}

impl crc64 {
    /// initialize for little-endian 64 bits Cyclic Redundancy Check
    pub fn new_le(poly: u64) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc64le_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculate for little-endian 64 bits Cyclic Redundancy Check
    pub fn le(self, data: &[u8], value: u64) -> u64 {
        unsafe { a_crc64le(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }

    /// initialize for big-endian 64 bits Cyclic Redundancy Check
    pub fn new_be(poly: u64) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc64be_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }

    /// calculate for big-endian 64 bits Cyclic Redundancy Check
    pub fn be(self, data: &[u8], value: u64) -> u64 {
        unsafe { a_crc64be(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
}

#[test]
fn crc64() {
    {
        let ctx = crate::crc::crc64::new_le(POLY64);
        ctx.le(b"", INIT64);
    }
    {
        let ctx = crate::crc::crc64::new_be(POLY64);
        ctx.be(b"", INIT64);
    }
}
