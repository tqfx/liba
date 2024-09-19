#[cfg(not(feature = "cmake"))]
fn main() {
    let mut make = cc::Build::new();
    make.include("include");
    make.define("A_EXPORTS", None);
    #[cfg(feature = "float")]
    make.define("A_SIZE_FLOAT", "4");
    #[cfg(feature = "static_crt")]
    make.static_crt(true);
    make.file("src/a.c")
        .file("src/avl.c")
        .file("src/buf.c")
        .file("src/complex.c")
        .file("src/crc.c")
        .file("src/fuzzy.c")
        .file("src/math.c")
        .file("src/mf.c")
        .file("src/pid.c")
        .file("src/pid_fuzzy.c")
        .file("src/pid_neuro.c")
        .file("src/poly.c")
        .file("src/que.c")
        .file("src/rbt.c")
        .file("src/regress.c")
        .file("src/regress_linear.c")
        .file("src/regress_simple.c")
        .file("src/str.c")
        .file("src/tf.c")
        .file("src/trajbell.c")
        .file("src/trajpoly3.c")
        .file("src/trajpoly5.c")
        .file("src/trajpoly7.c")
        .file("src/trajtrap.c")
        .file("src/utf.c")
        .file("src/vec.c")
        .file("src/version.c")
        .compile("a");
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
