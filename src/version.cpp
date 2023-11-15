#include "a/version.h"

namespace a
{

version::version(char const *ver)
    : major(0)
    , minor(0)
    , patch(0)
{
    a_version_parse(this, ver);
}

bool version::operator<(version const &ver) const
{
    return a_version_lt(this, &ver);
}

bool version::operator>(version const &ver) const
{
    return a_version_gt(this, &ver);
}

bool version::operator<=(version const &ver) const
{
    return a_version_le(this, &ver);
}

bool version::operator>=(version const &ver) const
{
    return a_version_ge(this, &ver);
}

bool version::operator==(version const &ver) const
{
    return a_version_eq(this, &ver);
}

bool version::operator!=(version const &ver) const
{
    return a_version_ne(this, &ver);
}

unsigned int version_major(void)
{
    return VERSION_MAJOR;
}

unsigned int version_minor(void)
{
    return VERSION_MINOR;
}

unsigned int version_patch(void)
{
    return VERSION_PATCH;
}

} /* namespace a */
