#include "BrainTwister/JSON.h"
#include "BrainTwister/Record.h"
#include "BrainTwister/XML.h"
#include "gtest/gtest.h"
#include <vector>

// Test nested structures

BRAINTWISTER_RECORD(Record4, \
    ((int, i, 3)) \
    ((double, d, 2.7)) \
)

BRAINTWISTER_RECORD(Record5, \
    ((int, i, 5)) \
    ((Record4, record1, Record4{})) \
)

BRAINTWISTER_RECORD(Record6, \
    ((int, i, 7)) \
    ((Record4, record1, Record4{}.set_i(125).set_d(30.7))) \
)

TEST(Record3Test, default1)
{
    Record4 record1;

    EXPECT_EQ(3, record1.i);
    EXPECT_EQ(2.7, record1.d);
}

TEST(Record3Test, default2)
{
    Record5 record2;

    EXPECT_EQ(5, record2.i);
    EXPECT_EQ(3, record2.record1.i);
    EXPECT_EQ(2.7, record2.record1.d);
}

TEST(Record3Test, default3)
{
    Record6 record3;

    EXPECT_EQ(7, record3.i);
    EXPECT_EQ(125, record3.record1.i);
    EXPECT_EQ(30.7, record3.record1.d);
}

TEST(Record3Test, GenericLoader_int)
{
    boost::property_tree::ptree tree;
    tree.put("i", "42");
    auto i = BrainTwister::RecordDetails::GenericLoader<int>()(tree, "i", 5);

    EXPECT_EQ(42, i);
}

TEST(Record3Test, GenericLoader_record)
{
    boost::property_tree::ptree leaf;
    leaf.put("i", "1");
    leaf.put("d", "2.5");
    boost::property_tree::ptree tree;
    tree.add_child("record1", leaf);
    auto record1 = BrainTwister::RecordDetails::GenericLoader<Record4>()(tree, "record1", Record4());

    EXPECT_EQ(1, record1.i);
}

TEST(Record3Test, json1)
{
    auto json = JSON{"{\"i\": 42, \"record1\": {\"i\": 33, \"d\": 3.8}}"};
    auto i = BrainTwister::RecordDetails::GenericLoader<int>()(json.get_ptree(), "i", 0);
    auto record1 = BrainTwister::RecordDetails::GenericLoader<Record4>()(json.get_ptree(), "record1", Record4());

    EXPECT_EQ(42, i);
    EXPECT_EQ(33, record1.i);
    EXPECT_EQ(3.8, record1.d);
}

TEST(Record3Test, json2)
{
    auto json = JSON{"{\"i\": 42, \"record1\": {\"i\": 33, \"d\": 3.8}}"};
    auto record2 = Record5(json.get_ptree());

    EXPECT_EQ(42, record2.i);
    EXPECT_EQ(33, record2.record1.i);
    EXPECT_EQ(3.8, record2.record1.d);
}

TEST(Record3Test, json3)
{
    Record5 record2{JSON{"{\"i\": 42, \"record1\": {\"i\": 33, \"d\": 3.8}}"}};

    EXPECT_EQ(42, record2.i);
    EXPECT_EQ(33, record2.record1.i);
    EXPECT_EQ(3.8, record2.record1.d);
}

TEST(Record3Test, xml)
{
    Record5 record2{XML{"<i>42</i><record1><i>33</i><d>3.8</d></record1>"}};

    EXPECT_EQ(42, record2.i);
    EXPECT_EQ(33, record2.record1.i);
    EXPECT_EQ(3.8, record2.record1.d);
}
