#include "BrainTwister/JSON.h"
#include "BrainTwister/XML.h"
#include "gtest/gtest.h"
#include "nested.h"

TEST(nested, default1)
{
    Nested1 nested1;

    EXPECT_EQ(3, nested1.i);
    EXPECT_EQ(2.7, nested1.d);
}

TEST(nested, default2)
{
    Nested2 nested2;

    EXPECT_EQ(5, nested2.i);
    EXPECT_EQ(3, nested2.nested1.i);
    EXPECT_EQ(2.7, nested2.nested1.d);
}

TEST(nested, default3)
{
    Nested3 nested3;

    EXPECT_EQ(7, nested3.i);
    EXPECT_EQ(125, nested3.nested1.i);
    EXPECT_EQ(30.7, nested3.nested1.d);
}

TEST(nested, GenericLoader_int)
{
    boost::property_tree::ptree tree;
    tree.put("i", "42");
    auto i = BrainTwister::RecordDetails::GenericLoader<int>()(tree, "i", 5);

    EXPECT_EQ(42, i);
}

TEST(nested, GenericLoader_nested)
{
    boost::property_tree::ptree leaf;
    leaf.put("i", "1");
    leaf.put("d", "2.5");
    boost::property_tree::ptree tree;
    tree.add_child("nested1", leaf);
    auto nested1 = BrainTwister::RecordDetails::GenericLoader<Nested1>()(tree, "nested1", Nested1());

    EXPECT_EQ(1, nested1.i);
}

TEST(nested, json)
{
    Nested2 nested{JSON{R"(
        {
            "i": 42,
            "nested1":
            {
                "i": 33,
                "d": 3.8
            }
        }
    )"}};

    EXPECT_EQ(42, nested.i);
    EXPECT_EQ(33, nested.nested1.i);
    EXPECT_EQ(3.8, nested.nested1.d);
}

TEST(nested, xml)
{
    Nested2 nested2{XML{R"(
       <i>42</i>
       <nested1>
           <i>33</i>
           <d>3.8</d>
       </nested1>
    )"}};

    EXPECT_EQ(42, nested2.i);
    EXPECT_EQ(33, nested2.nested1.i);
    EXPECT_EQ(3.8, nested2.nested1.d);
}
