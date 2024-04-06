import os
AddOption('--float', choices=('4', '8', '16'), default=8, metavar='4,8,16', help='floating-point number bytes')
AddOption('--tools', default='', help='append the default tool list')
vars = Variables()
vars.Add('CC', help='The C compiler')
vars.Add('CFLAGS', help='The C compiler flags')
vars.Add('LINKFLAGS', help='The linker flags')
env = Environment(
    ENV=os.environ.copy(),
    tools=['default'] + GetOption('tools').split(','),
    variables=vars,
)
env.Append(CPPPATH=('include'))
env.Append(CPPDEFINES=('A_EXPORTS'))
env.Append(CPPDEFINES=('A_HAVA_H', '"a.scons.h"'))
def Undefine(conf):
    if '\n' not in conf.config_h_text:
        return
    conf.config_h_text = conf.config_h_text.replace(
        conf.config_h_text.splitlines()[-1] + '\n', ''
    )
conf = env.Configure(config_h='include/a/a.scons.h')
A_SIZE_POINTER = conf.CheckTypeSize('void *')
Undefine(conf)
conf.Define('A_SIZE_POINTER', A_SIZE_POINTER)
res = conf.TryRun('''#include <stdio.h>
int main()
{
    int const x = 1;
    printf("%s", *(char *)&x ? "1234" : "4321");
    return 0;
}\n''', '.c')
if res[0]:
    conf.Define('A_BYTE_ORDER', res[1], 'The byte order of compiler target architecture.')
A_SIZE_FLOAT = int(env.GetOption('float'))
conf.Define('A_SIZE_FLOAT', A_SIZE_FLOAT, "The size of `a_float', as computed by sizeof.")
conf.CheckLib('m')
Undefine(conf)
for func in (
    'expm1', 'log1p', 'hypot', 'atan2',
    'csqrt', 'cpow', 'cexp', 'clog',
    'csin', 'ccos', 'ctan',
    'csinh', 'ccosh', 'ctanh',
    'casin', 'cacos', 'catan',
    'casinh', 'cacosh', 'catanh'
):
    name = 'A_HAVE_' + func.upper()
    if A_SIZE_FLOAT == 0x10:
        func += 'l'
    if A_SIZE_FLOAT == 0x04:
        func += 'f'
    ok = conf.CheckFunc(func)
    Undefine(conf)
    if ok:
        conf.Define(name, '1')
env = conf.Finish()
a = env.SharedObject(env.Glob('src/*.c') + env.Glob('src/*/*.c'))
if env['PLATFORM'] == 'win32':
    liba = env.SharedLibrary('liba', a)
else:
    liba = env.SharedLibrary('a', a)
alib = env.StaticLibrary('a', a)
env.Install()
if env.GetOption('install_sandbox'):
    include = env.Install('include', source='include/a')
    def install_fixup(source, target, env):
        source = source[0].get_relpath() + '/a.h'
        target = target[0].get_relpath() + '/a.h'
        with open(source, "r") as f:
            text = f.read()
        cur = "#if defined(A_HAVE_H)"
        new = '#include "a.scons.h"\n' + cur
        text = text.replace(cur, new)
        with open(target, "wb") as f:
            f.write(text.encode())
    env.AddPostAction(include, install_fixup)
    env.Install('lib', source=[alib, liba])
