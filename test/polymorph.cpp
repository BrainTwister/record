#include "BrainTwister/JSON.h"
#include "BrainTwister/XML.h"
#include "gtest/gtest.h"
#include "polymorph.h"

TEST(polymorph, default)
{
    Polymorph polymorph;

    EXPECT_EQ(std::shared_ptr<RecordBase>(), polymorph.p1);
    EXPECT_EQ(std::shared_ptr<RecordDerived1>(), polymorph.p2);
}

TEST(polymorph, parameter_constructor)
{
    std::shared_ptr<RecordBase> p1{new RecordDerived1{4}};
    Polymorph polymorph(p1);

    EXPECT_EQ(4, std::dynamic_pointer_cast<RecordDerived1>(polymorph.p1)->i);
}

TEST(polymorph, json)
{
    Polymorph polymorph{JSON{"{\"p1\": {\"RecordDerived1\": {\"i\": 42}}}"}};

    EXPECT_EQ(42, std::dynamic_pointer_cast<RecordDerived1>(polymorph.p1)->i);
}

TEST(polymorph, json2)
{
    Polymorph polymorph{JSON{"{\"p1\": {\"RecordDerived1\": {\"i\": 42}}, \"p2\": {\"RecordDerived2\": {\"d\": 3.9}}}"}};

    EXPECT_EQ(42, std::dynamic_pointer_cast<RecordDerived1>(polymorph.p1)->i);
    EXPECT_EQ(3.9, std::dynamic_pointer_cast<RecordDerived2>(polymorph.p2)->d);

    EXPECT_EQ(42, polymorph.p1->operator()());
}
