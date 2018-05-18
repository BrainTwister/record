#pragma once

#include "BrainTwister/Record.h"
#include <list>
#include <vector>

BRAINTWISTER_RECORD(Collection1, \
    ((int, i, 0)) \
    ((double, d, 0.0)) \
    ((std::string, s, "foo")) \
)

BRAINTWISTER_RECORD(Collection2, \
    ((std::vector<int>, v1, std::vector<int>())) \
    ((std::vector<Collection1>, v2, std::vector<Collection1>())) \
)

BRAINTWISTER_RECORD(Collection3, \
    ((std::list<int>, list, std::list<int>())) \
)
