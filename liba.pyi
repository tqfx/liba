from typing import Iterable, overload
from array import array
import math

class i8:
    @staticmethod
    def array(o: object) -> array[int]: ...

class u8:
    @staticmethod
    def array(o: object) -> array[int]: ...

class i16:
    @staticmethod
    def array(o: object) -> array[int]: ...

class u16:
    @staticmethod
    def array(o: object) -> array[int]: ...

class i32:
    @staticmethod
    def array(o: object) -> array[int]: ...

class u32:
    @staticmethod
    def array(o: object) -> array[int]: ...
    @staticmethod
    def sqrt(x: int) -> tuple[int, int]: ...

class i64:
    @staticmethod
    def array(o: object) -> array[int]: ...

class u64:
    @staticmethod
    def array(o: object) -> array[int]: ...
    @staticmethod
    def sqrt(x: int) -> tuple[int, int]: ...

class f32:
    @staticmethod
    def array(o: object) -> array[float]: ...
    @staticmethod
    @overload
    def rsqrt(x: Iterable[float]) -> array[float]: ...
    @staticmethod
    @overload
    def rsqrt(x: float) -> float: ...

class f64:
    @staticmethod
    def array(o: object) -> array[float]: ...
    @staticmethod
    @overload
    def rsqrt(x: Iterable[float]) -> array[float]: ...
    @staticmethod
    @overload
    def rsqrt(x: float) -> float: ...

class float_:
    @staticmethod
    def array(o: object) -> array[float]: ...

class hash:
    @staticmethod
    def bkdr(str: bytes, val: int) -> int: ...

class crc8:
    POLY: int
    INIT: int
    def __init__(self, poly=POLY, high=False) -> None: ...
    def __call__(self, data: bytes, init=INIT) -> int: ...
    @property
    def table(self) -> array[int]: ...

class crc16:
    POLY: int
    INIT: int
    def __init__(self, poly=POLY, high=False) -> None: ...
    def __call__(self, data: bytes, init=INIT) -> int: ...
    @property
    def table(self) -> array[int]: ...

class crc32:
    POLY: int
    INIT: int
    def __init__(self, poly=POLY, high=False) -> None: ...
    def __call__(self, data: bytes, init=INIT) -> int: ...
    @property
    def table(self) -> array[int]: ...

class crc64:
    POLY: int
    INIT: int
    def __init__(self, poly=POLY, high=False) -> None: ...
    def __call__(self, data: bytes, init=INIT) -> int: ...
    @property
    def table(self) -> array[int]: ...

class mf:
    NUL: int
    GAUSS: int
    GAUSS2: int
    GBELL: int
    SIG: int
    DSIG: int
    PSIG: int
    TRAP: int
    TRI: int
    LINS: int
    LINZ: int
    S: int
    Z: int
    PI: int
    @staticmethod
    @overload
    def __call__(e: int, x: Iterable[float], a: Iterable[float]) -> array[float]: ...
    @staticmethod
    @overload
    def __call__(e: int, x: float, a: Iterable[float]) -> float: ...
    @staticmethod
    @overload
    def gauss(x: Iterable[float], sigma: float, c: float) -> array[float]: ...
    @staticmethod
    @overload
    def gauss(x: float, sigma: float, c: float) -> float: ...
    @staticmethod
    @overload
    def gauss2(
        x: Iterable[float], sigma1: float, c1: float, sigma2: float, c2: float
    ) -> array[float]: ...
    @staticmethod
    @overload
    def gauss2(x: float, sigma1: float, c1: float, sigma2: float, c2: float) -> float: ...
    @staticmethod
    @overload
    def gbell(x: Iterable[float], a: float, b: float, c: float) -> array[float]: ...
    @staticmethod
    @overload
    def gbell(x: float, a: float, b: float, c: float) -> float: ...
    @staticmethod
    @overload
    def sig(x: Iterable[float], a: float, c: float) -> array[float]: ...
    @staticmethod
    @overload
    def sig(x: float, a: float, c: float) -> float: ...
    @staticmethod
    @overload
    def dsig(x: Iterable[float], a1: float, c1: float, a2: float, c2: float) -> array[float]: ...
    @staticmethod
    @overload
    def dsig(x: float, a1: float, c1: float, a2: float, c2: float) -> float: ...
    @staticmethod
    @overload
    def psig(x: Iterable[float], a1: float, c1: float, a2: float, c2: float) -> array[float]: ...
    @staticmethod
    @overload
    def psig(x: float, a1: float, c1: float, a2: float, c2: float) -> float: ...
    @staticmethod
    @overload
    def trap(x: Iterable[float], a: float, b: float, c: float, d: float) -> array[float]: ...
    @staticmethod
    @overload
    def trap(x: float, a: float, b: float, c: float, d: float) -> float: ...
    @staticmethod
    @overload
    def tri(x: Iterable[float], a: float, b: float, c: float) -> array[float]: ...
    @staticmethod
    @overload
    def tri(x: float, a: float, b: float, c: float) -> float: ...
    @staticmethod
    @overload
    def lins(x: Iterable[float], a: float, b: float) -> array[float]: ...
    @staticmethod
    @overload
    def lins(x: float, a: float, b: float) -> float: ...
    @staticmethod
    @overload
    def linz(x: Iterable[float], a: float, b: float) -> array[float]: ...
    @staticmethod
    @overload
    def linz(x: float, a: float, b: float) -> float: ...
    @staticmethod
    @overload
    def s(x: Iterable[float], a: float, b: float) -> array[float]: ...
    @staticmethod
    @overload
    def s(x: float, a: float, b: float) -> float: ...
    @staticmethod
    @overload
    def z(x: Iterable[float], a: float, b: float) -> array[float]: ...
    @staticmethod
    @overload
    def z(x: float, a: float, b: float) -> float: ...
    @staticmethod
    @overload
    def pi(x: Iterable[float], a: float, b: float, c: float, d: float) -> array[float]: ...
    @staticmethod
    @overload
    def pi(x: float, a: float, b: float, c: float, d: float) -> float: ...

class pid:
    OFF: int
    POS: int
    INC: int
    def __init__(self, min=-math.inf, max=+math.inf, sum=0.0) -> None: ...
    def kpid(self, kp: float, ki: float, kd: float) -> pid: ...
    def __call__(self, set: float, fdb: float) -> float: ...
    def zero(self) -> pid: ...
    @property
    def mode(self) -> int: ...
    @mode.setter
    def mode(self, mode: int) -> None: ...
    @property
    def kp(self) -> float: ...
    @kp.setter
    def kp(self, kp: float) -> None: ...
    @property
    def ki(self) -> float: ...
    @ki.setter
    def ki(self, ki: float) -> None: ...
    @property
    def kd(self) -> float: ...
    @kd.setter
    def kd(self, kd: float) -> None: ...
    @property
    def summax(self) -> float: ...
    @summax.setter
    def summax(self, summax: float) -> None: ...
    @property
    def outmax(self) -> float: ...
    @outmax.setter
    def outmax(self, outmax: float) -> None: ...
    @property
    def outmin(self) -> float: ...
    @outmin.setter
    def outmin(self, outmin: float) -> None: ...
    @property
    def out(self) -> float: ...
    @property
    def fdb(self) -> float: ...
    @property
    def err(self) -> float: ...

class pid_fuzzy:
    CAP: int
    CAP_ALGEBRA: int
    CAP_BOUNDED: int
    CUP: int
    CUP_ALGEBRA: int
    CUP_BOUNDED: int
    EQU: int
    def __init__(self, min=-math.inf, max=+math.inf, sum=0.0) -> None: ...
    def op(self, op: int) -> pid_fuzzy: ...
    def rule(
        self,
        me: Iterable[Iterable[float]],
        mec: Iterable[Iterable[float]],
        mkp: Iterable[Iterable[float]],
        mki: Iterable[Iterable[float]],
        mkd: Iterable[Iterable[float]],
    ) -> pid_fuzzy: ...
    def joint(self, num: int) -> pid_fuzzy: ...
    def kpid(self, kp: float, ki: float, kd: float) -> pid_fuzzy: ...
    def __call__(self, set: float, fdb: float) -> float: ...
    def zero(self) -> pid_fuzzy: ...
    @property
    def mode(self) -> int: ...
    @mode.setter
    def mode(self, mode: int) -> None: ...
    @property
    def kp(self) -> float: ...
    @kp.setter
    def kp(self, kp: float) -> None: ...
    @property
    def ki(self) -> float: ...
    @ki.setter
    def ki(self, ki: float) -> None: ...
    @property
    def kd(self) -> float: ...
    @kd.setter
    def kd(self, kd: float) -> None: ...
    @property
    def summax(self) -> float: ...
    @summax.setter
    def summax(self, summax: float) -> None: ...
    @property
    def outmax(self) -> float: ...
    @outmax.setter
    def outmax(self, outmax: float) -> None: ...
    @property
    def outmin(self) -> float: ...
    @outmin.setter
    def outmin(self, outmin: float) -> None: ...
    @property
    def out(self) -> float: ...
    @property
    def fdb(self) -> float: ...
    @property
    def err(self) -> float: ...
    @property
    def order(self) -> int: ...

class pid_neuron:
    def __init__(self, min=-math.inf, max=+math.inf, sum=0.0) -> None: ...
    def kpid(self, k: float, kp: float, ki: float, kd: float) -> pid_neuron: ...
    def wpid(self, wp: float, wi: float, wd: float) -> pid_neuron: ...
    def __call__(self, set: float, fdb: float) -> float: ...
    def zero(self) -> pid_neuron: ...
    @property
    def mode(self) -> int: ...
    @mode.setter
    def mode(self, mode: int) -> None: ...
    @property
    def k(self) -> float: ...
    @k.setter
    def k(self, k: float) -> None: ...
    @property
    def kp(self) -> float: ...
    @kp.setter
    def kp(self, kp: float) -> None: ...
    @property
    def ki(self) -> float: ...
    @ki.setter
    def ki(self, ki: float) -> None: ...
    @property
    def kd(self) -> float: ...
    @kd.setter
    def kd(self, kd: float) -> None: ...
    @property
    def wp(self) -> float: ...
    @wp.setter
    def wp(self, wp: float) -> None: ...
    @property
    def wi(self) -> float: ...
    @wi.setter
    def wi(self, wi: float) -> None: ...
    @property
    def wd(self) -> float: ...
    @wd.setter
    def wd(self, wd: float) -> None: ...
    @property
    def summax(self) -> float: ...
    @summax.setter
    def summax(self, summax: float) -> None: ...
    @property
    def outmax(self) -> float: ...
    @outmax.setter
    def outmax(self, outmax: float) -> None: ...
    @property
    def outmin(self) -> float: ...
    @outmin.setter
    def outmin(self, outmin: float) -> None: ...
    @property
    def out(self) -> float: ...
    @property
    def fdb(self) -> float: ...
    @property
    def err(self) -> float: ...
    @property
    def ec(self) -> float: ...

@overload
def poly_eval(x: Iterable[float], *a: float) -> array[float]: ...
@overload
def poly_eval(x: float, *a: float) -> float: ...
@overload
def poly_evar(x: Iterable[float], *a: float) -> array[float]: ...
@overload
def poly_evar(x: float, *a: float) -> float: ...

class polytrack3:
    def __init__(
        self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float = 0,
        v1: float = 0,
    ) -> None: ...
    def gen(
        self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float = 0,
        v1: float = 0,
    ) -> polytrack3: ...
    @overload
    def __call__(self, dt: Iterable[float]) -> tuple[array[float], array[float], array[float]]: ...
    @overload
    def __call__(self, dt: float) -> tuple[float, float, float]: ...
    @overload
    def pos(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def pos(self, dt: float) -> float: ...
    @overload
    def vel(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def vel(self, dt: float) -> float: ...
    @overload
    def acc(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def acc(self, dt: float) -> float: ...
    @property
    def k(self) -> array[float]: ...

class polytrack5:
    def __init__(
        self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float = 0,
        v1: float = 0,
        a0: float = 0,
        a1: float = 0,
    ) -> None: ...
    def gen(
        self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float = 0,
        v1: float = 0,
        a0: float = 0,
        a1: float = 0,
    ) -> polytrack5: ...
    @overload
    def __call__(self, dt: Iterable[float]) -> tuple[array[float], array[float], array[float]]: ...
    @overload
    def __call__(self, dt: float) -> tuple[float, float, float]: ...
    @overload
    def pos(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def pos(self, dt: float) -> float: ...
    @overload
    def vel(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def vel(self, dt: float) -> float: ...
    @overload
    def acc(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def acc(self, dt: float) -> float: ...
    @property
    def k(self) -> array[float]: ...

class polytrack7:
    def __init__(
        self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float = 0,
        v1: float = 0,
        a0: float = 0,
        a1: float = 0,
        j0: float = 0,
        j1: float = 0,
    ) -> None: ...
    def gen(
        self,
        t0: float,
        t1: float,
        q0: float,
        q1: float,
        v0: float = 0,
        v1: float = 0,
        a0: float = 0,
        a1: float = 0,
        j0: float = 0,
        j1: float = 0,
    ) -> polytrack7: ...
    @overload
    def __call__(
        self, dt: Iterable[float]
    ) -> tuple[array[float], array[float], array[float], array[float]]: ...
    @overload
    def __call__(self, dt: float) -> tuple[float, float, float, float]: ...
    @overload
    def pos(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def pos(self, dt: float) -> float: ...
    @overload
    def vel(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def vel(self, dt: float) -> float: ...
    @overload
    def acc(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def acc(self, dt: float) -> float: ...
    @overload
    def jer(self, dt: Iterable[float]) -> array[float]: ...
    @overload
    def jer(self, dt: float) -> float: ...
    @property
    def k(self) -> array[float]: ...

class tf:
    def __init__(self, num: Iterable[float], den: Iterable[float]) -> None: ...
    @property
    def input(self) -> array[float]: ...
    @property
    def num(self) -> array[float]: ...
    @num.setter
    def num(self, num: Iterable[float]) -> None: ...
    @property
    def output(self) -> array[float]: ...
    @property
    def den(self) -> array[float]: ...
    @den.setter
    def den(self, den: Iterable[float]) -> None: ...
    def __call__(self, x: float) -> float: ...
    def zero(self) -> tf: ...

def version_check(major: int = 0, minor: int = 0, patch: int = 0) -> int: ...

class version:
    def __init__(self, major: int = 0, minor: int = 0, patch: int = 0) -> None: ...
    def __lt__(self, other: version) -> bool: ...
    def __gt__(self, other: version) -> bool: ...
    def __le__(self, other: version) -> bool: ...
    def __ge__(self, other: version) -> bool: ...
    def __eq__(self, other: version) -> bool: ...
    def __ne__(self, other: version) -> bool: ...
    def parse(self, ver: bytes) -> version: ...
    @property
    def major(self) -> int: ...
    @major.setter
    def major(self, major: int) -> None: ...
    @property
    def minor(self) -> int: ...
    @minor.setter
    def minor(self, minor: int) -> None: ...
    @property
    def patch(self) -> int: ...
    @patch.setter
    def patch(self, patch: int) -> None: ...

VERSION_TWEAK: int
VERSION_PATCH: int
VERSION_MINOR: int
VERSION_MAJOR: int
VERSION: str
