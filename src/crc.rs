//! Cyclic Redundancy Check

/// Cyclic Redundancy Check for 8 bits
#[repr(C)]
pub struct crc8 {
    /// Cyclic Redundancy Check comparison table
    table: [u8; 0x100],
}

extern "C" {
    fn a_crc8m_init(table: *mut u8, poly: u8);
    fn a_crc8l_init(table: *mut u8, poly: u8);
    fn a_crc8(table: *const u8, pdate: *const u8, nbyte: usize, value: u8) -> u8;
}

impl crc8 {
    /// initialize for MSB CRC-8
    pub fn new_msb(poly: u8) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc8m_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// initialize for LSB CRC-8
    pub fn new_lsb(poly: u8) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc8l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// calculate for MSB CRC-8
    pub fn msb(self, data: &[u8], value: u8) -> u8 {
        unsafe { a_crc8(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
    /// calculate for LSB CRC-8
    pub fn lsb(self, data: &[u8], value: u8) -> u8 {
        unsafe { a_crc8(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
}

#[test]
fn crc8() {
    extern crate std;
    {
        let ctx = crate::crc::crc16::new_msb(0x31);
        let res = ctx.msb(b"123456789", 0xFFFF);
        std::println!("0x{:X}", res ^ 0xFF);
    }
    {
        let ctx = crate::crc::crc16::new_lsb(0x8C);
        let res = ctx.lsb(b"123456789", 0xFFFF);
        std::println!("0x{:X}", res ^ 0xFF);
    }
}

/// Cyclic Redundancy Check for 16 bits
#[repr(C)]
pub struct crc16 {
    /// Cyclic Redundancy Check comparison table
    table: [u16; 0x100],
}

extern "C" {
    fn a_crc16m_init(table: *mut u16, poly: u16);
    fn a_crc16l_init(table: *mut u16, poly: u16);
    fn a_crc16m(table: *const u16, pdate: *const u8, nbyte: usize, value: u16) -> u16;
    fn a_crc16l(table: *const u16, pdate: *const u8, nbyte: usize, value: u16) -> u16;
}

impl crc16 {
    /// initialize for MSB CRC-16
    pub fn new_msb(poly: u16) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc16m_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// initialize for LSB CRC-16
    pub fn new_lsb(poly: u16) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc16l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// calculate for MSB CRC-16
    pub fn msb(self, data: &[u8], value: u16) -> u16 {
        unsafe { a_crc16m(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
    /// calculate for LSB CRC-16
    pub fn lsb(self, data: &[u8], value: u16) -> u16 {
        unsafe { a_crc16l(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
}

#[test]
fn crc16() {
    extern crate std;
    {
        let ctx = crate::crc::crc16::new_msb(0x8005);
        let res = ctx.msb(b"123456789", 0xFFFF);
        std::println!("0x{:X}", res ^ 0xFFFF);
    }
    {
        let ctx = crate::crc::crc16::new_lsb(0xA001);
        let res = ctx.lsb(b"123456789", 0xFFFF);
        std::println!("0x{:X}", res ^ 0xFFFF);
    }
}

/// Cyclic Redundancy Check for 32 bits
#[repr(C)]
pub struct crc32 {
    /// Cyclic Redundancy Check comparison table
    table: [u32; 0x100],
}

extern "C" {
    fn a_crc32m_init(table: *mut u32, poly: u32);
    fn a_crc32l_init(table: *mut u32, poly: u32);
    fn a_crc32m(table: *const u32, pdate: *const u8, nbyte: usize, value: u32) -> u32;
    fn a_crc32l(table: *const u32, pdate: *const u8, nbyte: usize, value: u32) -> u32;
}

impl crc32 {
    /// initialize for MSB CRC-32
    pub fn new_msb(poly: u32) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc32m_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// initialize for LSB CRC-32
    pub fn new_lsb(poly: u32) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc32l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// calculate for MSB CRC-32
    pub fn msb(self, data: &[u8], value: u32) -> u32 {
        unsafe { a_crc32m(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
    /// calculate for LSB CRC-32
    pub fn lsb(self, data: &[u8], value: u32) -> u32 {
        unsafe { a_crc32l(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
}

#[test]
fn crc32() {
    extern crate std;
    {
        let ctx = crate::crc::crc32::new_msb(0x04C11DB7);
        let res = ctx.msb(b"123456789", 0xFFFFFFFF);
        std::println!("0x{:X}", res ^ 0xFFFFFFFF);
    }
    {
        let ctx = crate::crc::crc32::new_lsb(0xEDB88320);
        let res = ctx.lsb(b"123456789", 0xFFFFFFFF);
        std::println!("0x{:X}", res ^ 0xFFFFFFFF);
    }
}

/// Cyclic Redundancy Check for 64 bits
#[repr(C)]
pub struct crc64 {
    /// Cyclic Redundancy Check comparison table
    table: [u64; 0x100],
}

extern "C" {
    fn a_crc64m_init(table: *mut u64, poly: u64);
    fn a_crc64l_init(table: *mut u64, poly: u64);
    fn a_crc64m(table: *const u64, pdate: *const u8, nbyte: usize, value: u64) -> u64;
    fn a_crc64l(table: *const u64, pdate: *const u8, nbyte: usize, value: u64) -> u64;
}

impl crc64 {
    /// initialize for MSB CRC-64
    pub fn new_msb(poly: u64) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc64m_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// initialize for LSB CRC-64
    pub fn new_lsb(poly: u64) -> Self {
        let mut ctx: Self = Self { table: [0; 0x100] };
        unsafe { a_crc64l_init(ctx.table.as_mut_ptr(), poly) };
        ctx
    }
    /// calculate for MSB CRC-64
    pub fn msb(self, data: &[u8], value: u64) -> u64 {
        unsafe { a_crc64m(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
    /// calculate for LSB CRC-64
    pub fn lsb(self, data: &[u8], value: u64) -> u64 {
        unsafe { a_crc64l(self.table.as_ptr(), data.as_ptr(), data.len(), value) }
    }
}

#[test]
fn crc64() {
    extern crate std;
    {
        let ctx = crate::crc::crc64::new_msb(0x42F0E1EBA9EA3693);
        let res = ctx.msb(b"123456789", 0xFFFFFFFFFFFFFFFF);
        std::println!("0x{:X}", res ^ 0xFFFFFFFFFFFFFFFF);
    }
    {
        let ctx = crate::crc::crc64::new_lsb(0xC96C5795D7870F42);
        let res = ctx.lsb(b"123456789", 0xFFFFFFFFFFFFFFFF);
        std::println!("0x{:X}", res ^ 0xFFFFFFFFFFFFFFFF);
    }
}
