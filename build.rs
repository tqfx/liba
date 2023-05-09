use cmake::Config;

fn main() {
    let mut config = Config::new("");

    config.define("BUILD_TESTING", "0");
    #[cfg(not(feature = "float"))]
    config.define("LIBA_REAL", "8");
    #[cfg(feature = "float")]
    config.define("LIBA_REAL", "4");
    config.static_crt(true);

    let out = config.build();
    let lib = out.join("lib");

    println!("cargo:rustc-link-search=native={}", lib.display());
    println!("cargo:rustc-link-lib=static={}", "a");
}
