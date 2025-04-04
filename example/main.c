#include "a/version.h"
#include "a/str.h"
#include <stdio.h>
int main(void)
{
    a_str *str = a_str_new();
    a_str_catf(str, "%u.%u.%u+%u",
               a_version_major,
               a_version_minor,
               a_version_patch,
               a_version_tweak);
    puts(a_str_ptr(str));
    a_str_die(str);
    return 0;
}
