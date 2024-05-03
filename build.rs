fn main() {
    let mut cmake = cmake::Config::new("");

    cmake.define("BUILD_TESTING", "0");
    #[cfg(not(feature = "float"))]
    cmake.define("LIBA_FLOAT", "8");
    #[cfg(feature = "float")]
    cmake.define("LIBA_FLOAT", "4");
    #[cfg(feature = "static_crt")]
    cmake.static_crt(true);

    let out = cmake.build();
    let lib = out.join("lib");

    println!("cargo:rustc-link-search=native={}", lib.display());
    println!("cargo:rustc-link-lib=static=a");
}
