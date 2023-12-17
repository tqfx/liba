#include "a/version.h"

namespace a
{

char const *const VERSION = A_VERSION;
unsigned int const version::MAJOR = A_VERSION_MAJOR;
unsigned int const version::MINOR = A_VERSION_MINOR;
unsigned int const version::PATCH = A_VERSION_PATCH;
a_u32_t const version::TWEAK = A_VERSION_TWEAK;

} /* namespace a */
