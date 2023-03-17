use cmake::Config;

fn main() {
    let mut config = Config::new("");

    config.define("BUILD_TESTING", "0");
    config.static_crt(true);

    let out = config.build();
    let lib = out.join("lib");

    println!("cargo:rustc-link-search=native={}", lib.display());
    println!("cargo:rustc-link-lib=static={}", "a");
}
