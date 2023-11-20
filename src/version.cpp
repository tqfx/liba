#include "a/version.h"

namespace a
{

unsigned int const version::MAJOR = A_VERSION_MAJOR;
unsigned int const version::MINOR = A_VERSION_MINOR;
unsigned int const version::PATCH = A_VERSION_PATCH;
a_u32_t const version::TWEAK = A_VERSION_TWEAK;
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

} /* namespace a */
