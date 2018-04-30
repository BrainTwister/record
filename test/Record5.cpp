// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BrainTwister
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#include "BrainTwister/JSON.h"
#include "BrainTwister/Record.h"
#include "BrainTwister/RecordBase.h"
#include "BrainTwister/RecordDerived.h"
#include "BrainTwister/Register.h"
#include "BrainTwister/XML.h"
#include "gtest/gtest.h"
#include <memory>
#include <string>

// Test polymorphism

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

BRAINTWISTER_RECORD(Record8, \
    ((std::shared_ptr<RecordBase>, p1, std::shared_ptr<RecordBase>())) \
    ((std::shared_ptr<RecordBase>, p2, std::shared_ptr<RecordDerived1>())) \
)

TEST(Record5Test, default)
{
    Record8 record;

    EXPECT_EQ(std::shared_ptr<RecordBase>(), record.p1);
    EXPECT_EQ(std::shared_ptr<RecordDerived1>(), record.p2);
}

TEST(Record5Test, parameter_constructor)
{
    std::shared_ptr<RecordBase> p1{new RecordDerived1{4}};
    Record8 record(p1);

    EXPECT_EQ(4, std::dynamic_pointer_cast<RecordDerived1>(record.p1)->i);
}

TEST(Record5Test, json)
{
	Record8 record5{JSON{"{\"p1\": {\"RecordDerived1\": {\"i\": 42}}}"}};

    EXPECT_EQ(42, std::dynamic_pointer_cast<RecordDerived1>(record5.p1)->i);
}

TEST(Record5Test, json2)
{
	Record8 record5{JSON{"{\"p1\": {\"RecordDerived1\": {\"i\": 42}}, \"p2\": {\"RecordDerived2\": {\"d\": 3.9}}}"}};

    EXPECT_EQ(42, std::dynamic_pointer_cast<RecordDerived1>(record5.p1)->i);
    EXPECT_EQ(3.9, std::dynamic_pointer_cast<RecordDerived2>(record5.p2)->d);

    EXPECT_EQ(42, record5.p1->operator()());
}
