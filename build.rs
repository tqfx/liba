#[cfg(not(feature = "cmake"))]
fn main() -> std::io::Result<()> {
    let mut make = cc::Build::new();
    make.include("include");
    make.define("A_EXPORTS", None);
    #[cfg(feature = "float")]
    make.define("A_SIZE_FLOAT", "4");
    #[cfg(feature = "static_crt")]
    make.static_crt(true);

    for entry in std::fs::read_dir("src")? {
        let path = entry?.path();
        let extension = path.extension().unwrap();
        if path.is_file() & extension.eq("c") {
            make.file(path);
        }
    }

    make.compile("a");
    Ok(())
}
#[cfg(feature = "cmake")]
fn main() {
    let mut cmake = cmake::Config::new("");

    cmake.define("BUILD_TESTING", "0");
    #[cfg(feature = "float")]
    cmake.define("LIBA_FLOAT", "4");
    #[cfg(feature = "static_crt")]
    cmake.static_crt(true);

    let out = cmake.build();
    let lib = out.join("lib");

    println!("cargo:rustc-link-search=native={}", lib.display());
    println!("cargo:rustc-link-lib=static=a");
}
