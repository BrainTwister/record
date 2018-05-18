#pragma once

#include "BrainTwister/Record.h"
#include "BrainTwister/RecordBase.h"
#include "BrainTwister/RecordDerived.h"
#include "BrainTwister/Register.h"
#include <memory>
#include <string>

BRAINTWISTER_RECORD_BASE(RecordBase, \
    ((std::string, s1, "base")), \
    virtual double operator ()() const = 0; \
)

BRAINTWISTER_RECORD_DERIVED(RecordDerived1, RecordBase, \
    ((int, i, 4)) \
    ((std::string, s2, "foo")), \
    virtual double operator ()() const { return i; } \
)

BRAINTWISTER_RECORD_DERIVED(RecordDerived2, RecordBase, \
    ((double, d, 2.3)) \
    ((std::string, s3, "bar")), \
    virtual double operator ()() const { return d; } \
)

BRAINTWISTER_RECORD_REGISTER(RecordBase, \
    (RecordDerived1) \
    (RecordDerived2) \
)

BRAINTWISTER_RECORD(Polymorph, \
    ((std::shared_ptr<RecordBase>, p1, std::shared_ptr<RecordBase>())) \
    ((std::shared_ptr<RecordBase>, p2, std::shared_ptr<RecordDerived1>())) \
)
