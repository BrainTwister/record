#pragma once

#include "BrainTwister/Record.h"
#include <memory>

BRAINTWISTER_RECORD(Pointer, \
    ((std::shared_ptr<int>, p, std::make_shared<int>(42))) \
)
