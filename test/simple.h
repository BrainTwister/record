#pragma once

#include "BrainTwister/Record.h"
#include <string>

BRAINTWISTER_RECORD(Simple, \
    ((int, i, 0)) \
    ((double, d, 0.0)) \
    ((std::string, s, "foo")) \
)
