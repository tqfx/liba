#include "a/version.h"

namespace a
{

uint_t version_major(void)
{
    return VERSION_MAJOR;
}

uint_t version_minor(void)
{
    return VERSION_MINOR;
}

uint_t version_patch(void)
{
    return VERSION_PATCH;
}

} /* namespace a */

a_bool_t a_version_s::operator<(a_version_s const &ver) const
{
    return a_version_lt(this, &ver);
}

a_bool_t a_version_s::operator>(a_version_s const &ver) const
{
    return a_version_gt(this, &ver);
}

a_bool_t a_version_s::operator<=(a_version_s const &ver) const
{
    return a_version_le(this, &ver);
}

a_bool_t a_version_s::operator>=(a_version_s const &ver) const
{
    return a_version_ge(this, &ver);
}

a_bool_t a_version_s::operator==(a_version_s const &ver) const
{
    return a_version_eq(this, &ver);
}

a_bool_t a_version_s::operator!=(a_version_s const &ver) const
{
    return a_version_ne(this, &ver);
}
