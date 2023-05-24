#include "a/version.h"

namespace a
{

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
