#pragma once

#include "BrainTwister/Record.h"

BRAINTWISTER_RECORD(Nested1, \
    ((int, i, 3)) \
    ((double, d, 2.7)) \
)

BRAINTWISTER_RECORD(Nested2, \
    ((int, i, 5)) \
    ((Nested1, nested1, Nested1{})) \
)

BRAINTWISTER_RECORD(Nested3, \
    ((int, i, 7)) \
    ((Nested1, nested1, Nested1{}.set_i(125).set_d(30.7))) \
)
