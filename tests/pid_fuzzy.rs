#[test]
#[allow(non_snake_case)]
fn pid_fuzzy() {
    use liba::float;
    use liba::mf::TRI;
    let NL: float = -3.0;
    let NM: float = -2.0;
    let NS: float = -1.0;
    let ZO: float = 0.0;
    let PS: float = 1.0;
    let PM: float = 2.0;
    let PL: float = 3.0;
    let me = [
        [TRI as float, NL, NL, NM],
        [TRI as float, NL, NM, NS],
        [TRI as float, NM, NS, ZO],
        [TRI as float, NS, ZO, PS],
        [TRI as float, ZO, PS, PM],
        [TRI as float, PS, PM, PL],
        [TRI as float, PM, PL, PL],
    ];
    let NL: float = -3.0;
    let NM: float = -2.0;
    let NS: float = -1.0;
    let ZO: float = 0.0;
    let PS: float = 1.0;
    let PM: float = 2.0;
    let PL: float = 3.0;
    let mec = [
        [TRI as float, NL, NL, NM],
        [TRI as float, NL, NM, NS],
        [TRI as float, NM, NS, ZO],
        [TRI as float, NS, ZO, PS],
        [TRI as float, ZO, PS, PM],
        [TRI as float, PS, PM, PL],
        [TRI as float, PM, PL, PL],
    ];
    let NL: float = -15.0;
    let NM: float = -10.0;
    let NS: float = -5.0;
    let ZO: float = 0.0;
    let PS: float = 5.0;
    let PM: float = 10.0;
    let PL: float = 15.0;
    let mkp = [
        [NL, NL, NM, NM, NS, ZO, ZO],
        [NL, NL, NM, NS, NS, ZO, PS],
        [NM, NM, NM, NS, ZO, PS, PS],
        [NM, NM, NS, ZO, PS, PM, PM],
        [NS, NS, ZO, PS, PS, PM, PM],
        [NS, ZO, PS, PM, PM, PM, PL],
        [ZO, ZO, PM, PM, PM, PL, PL],
    ];
    let NL: float = -3.0;
    let NM: float = -2.0;
    let NS: float = -1.0;
    let ZO: float = 0.0;
    let PS: float = 1.0;
    let PM: float = 2.0;
    let PL: float = 3.0;
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
    let mut fuzzy = [0u8; liba::pid_fuzzy::NFUZZ(2)];
    let mut pid = liba::pid_fuzzy::new();
    pid.rule(
        me.len(),
        &me.concat(),
        &mec.concat(),
        &mkp.concat(),
        &mki.concat(),
        &mkd.concat(),
    )
    .kpid(10.0, 0.1, 1.0)
    .set_nfuzz(&mut fuzzy, 2);
    pid.set_opr(liba::fuzzy::EQU).zero();
    std::println!("{} {}", pid.pos(1.0, 0.0), pid.pos(1.0, 0.0));
    pid.set_opr(liba::fuzzy::EQU).zero();
    std::println!("{} {}", pid.inc(1.0, 0.0), pid.inc(1.0, 0.0));
}
