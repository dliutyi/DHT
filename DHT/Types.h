#pragma once

#include <vector>

using byte_seq = std::vector<unsigned char>;

#ifdef _DEBUG
#define debug(...) printf(__VA_ARGS__);
#else
#define debug(...)
#endif