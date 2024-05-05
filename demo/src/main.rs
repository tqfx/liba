fn main() {
    println!(
        "{}.{}.{}+{}",
        liba::version::major(),
        liba::version::minor(),
        liba::version::patch(),
        liba::version::tweak()
    );
}
