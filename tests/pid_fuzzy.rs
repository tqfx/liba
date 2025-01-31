#[test]
#[allow(non_snake_case)]
fn pid_fuzzy() {
    use liba::real;
    use liba::mf::TRI;
    let NL: real = -3.0;
    let NM: real = -2.0;
    let NS: real = -1.0;
    let ZO: real = 0.0;
    let PS: real = 1.0;
    let PM: real = 2.0;
    let PL: real = 3.0;
    let me = [
        [TRI as real, NL, NL, NM],
        [TRI as real, NL, NM, NS],
        [TRI as real, NM, NS, ZO],
        [TRI as real, NS, ZO, PS],
        [TRI as real, ZO, PS, PM],
        [TRI as real, PS, PM, PL],
        [TRI as real, PM, PL, PL],
    ];
    let NL: real = -3.0;
    let NM: real = -2.0;
    let NS: real = -1.0;
    let ZO: real = 0.0;
    let PS: real = 1.0;
    let PM: real = 2.0;
    let PL: real = 3.0;
    let mec = [
        [TRI as real, NL, NL, NM],
        [TRI as real, NL, NM, NS],
        [TRI as real, NM, NS, ZO],
        [TRI as real, NS, ZO, PS],
        [TRI as real, ZO, PS, PM],
        [TRI as real, PS, PM, PL],
        [TRI as real, PM, PL, PL],
    ];
    let NL: real = -15.0;
    let NM: real = -10.0;
    let NS: real = -5.0;
    let ZO: real = 0.0;
    let PS: real = 5.0;
    let PM: real = 10.0;
    let PL: real = 15.0;
    let mkp = [
        [NL, NL, NM, NM, NS, ZO, ZO],
        [NL, NL, NM, NS, NS, ZO, PS],
        [NM, NM, NM, NS, ZO, PS, PS],
        [NM, NM, NS, ZO, PS, PM, PM],
        [NS, NS, ZO, PS, PS, PM, PM],
        [NS, ZO, PS, PM, PM, PM, PL],
        [ZO, ZO, PM, PM, PM, PL, PL],
    ];
    let NL: real = -3.0;
    let NM: real = -2.0;
    let NS: real = -1.0;
    let ZO: real = 0.0;
    let PS: real = 1.0;
    let PM: real = 2.0;
    let PL: real = 3.0;
    let mki = [
        [PL, PL, PM, PM, PS, ZO, ZO],
        [PL, PL, PM, PS, PS, ZO, ZO],
        [PL, PM, PS, PS, ZO, NS, NS],
        [PM, PM, PS, ZO, NS, NM, NM],
        [PM, PS, ZO, NS, NS, NM, NL],
        [ZO, ZO, NS, NS, NM, NL, NL],
        [ZO, ZO, NS, NM, NM, NL, NL],
    ];
    let mkd = [
        [NS, PS, PL, PL, PL, PM, NS],
        [NS, PS, PL, PM, PM, PS, ZO],
        [ZO, PS, PM, PM, PS, PS, ZO],
        [ZO, PS, PS, PS, PS, PS, ZO],
        [ZO, ZO, ZO, ZO, ZO, ZO, ZO],
        [NL, NS, NS, NS, NS, NS, NL],
        [NL, NM, NM, NM, NS, NS, NL],
    ];
    let mut fuzzy = [0u8; liba::pid_fuzzy::BFUZZ(2)];
    let mut pid = liba::pid_fuzzy::new();
    pid.set_rule(
        me.len(),
        &me.concat(),
        &mec.concat(),
        &mkp.concat(),
        &mki.concat(),
        &mkd.concat(),
    )
    .set_kpid(10.0, 0.1, 1.0)
    .set_bfuzz(&mut fuzzy, 2);
    pid.set_opr(liba::fuzzy::EQU).zero();
    std::println!("{} {}", pid.pos(1.0, 0.0), pid.pos(1.0, 0.0));
    pid.set_opr(liba::fuzzy::EQU).zero();
    std::println!("{} {}", pid.inc(1.0, 0.0), pid.inc(1.0, 0.0));
}
