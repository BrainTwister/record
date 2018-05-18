#include "BrainTwister/JSON.h"
#include "BrainTwister/XML.h"
#include "gtest/gtest.h"
#include "simple.h"

TEST(simple, default)
{
    Simple simple;

    EXPECT_EQ(0, simple.i);
    EXPECT_EQ(0.0, simple.d);
    EXPECT_EQ("foo", simple.s);
}

TEST(simple, parameter)
{
    Simple simple(42, 2.3);

    EXPECT_EQ(42, simple.i);
    EXPECT_EQ(2.3, simple.d);
}

TEST(simple, builder)
{
    Simple simple = Simple().set_i(16).set_d(3.9);

    EXPECT_EQ(16, simple.i);
    EXPECT_EQ(3.9, simple.d);
}

TEST(simple, builder_static)
{
    static Simple simple = Simple().set_i(16).set_d(3.9);

    EXPECT_EQ(16, simple.i);
    EXPECT_EQ(3.9, simple.d);
}

TEST(simple, copy_constructor)
{
    Simple s1(42, 2.3);
    Simple s2(s1);

    EXPECT_EQ(42, s2.i);
    EXPECT_EQ(2.3, s2.d);
}

TEST(simple, copy_operator)
{
    Simple s1 = Simple().set_i(16).set_d(3.9).set_s("bar");
    Simple s2 = s1;

    EXPECT_EQ(16, s2.i);
    EXPECT_EQ(3.9, s2.d);
    EXPECT_EQ("bar", s2.s);
}

TEST(simple, ptree)
{
    boost::property_tree::ptree pt;
    pt.put("i", "42");
    pt.put("d", "2.3");
    Simple simple(pt);

    EXPECT_EQ(42, simple.i);
    EXPECT_EQ(2.3, simple.d);
}

TEST(simple, json)
{
    Simple simple{JSON{R"(
        {
            "i": 42,
			"d": 3.8,
            "s": "bar"
        }
    )"}};

    EXPECT_EQ(42, simple.i);
    EXPECT_EQ(3.8, simple.d);
    EXPECT_EQ("bar", simple.s);
}

TEST(simple, json_unordered)
{
    Simple simple{JSON{R"(
        {
            "s": "bar",
            "i": 42,
			"d": 3.8
        }
    )"}};

    EXPECT_EQ(42, simple.i);
    EXPECT_EQ(3.8, simple.d);
    EXPECT_EQ("bar", simple.s);
}

TEST(simple, json_default)
{
    Simple simple{JSON{R"(
        {
            "i": 42
        }
    )"}};

    EXPECT_EQ(42, simple.i);
    EXPECT_EQ(0.0, simple.d);
    EXPECT_EQ("foo", simple.s);
}

TEST(simple, xml)
{
    Simple simple{XML{"<i>42</i><d>3.8</d><s>bar</s>"}};

    EXPECT_EQ(42, simple.i);
    EXPECT_EQ(3.8, simple.d);
    EXPECT_EQ("bar", simple.s);
}

TEST(simple, xml_unordered)
{
    Simple simple{XML{"<s>bar</s><i>42</i><d>3.8</d>"}};

    EXPECT_EQ(42, simple.i);
    EXPECT_EQ(3.8, simple.d);
    EXPECT_EQ("bar", simple.s);
}

TEST(simple, xml_default)
{
    Simple simple{XML{"<i>42</i>"}};

    EXPECT_EQ(42, simple.i);
    EXPECT_EQ(0.0, simple.d);
    EXPECT_EQ("foo", simple.s);
}

TEST(simple, compare)
{
    Simple s1(42, 2.3);
    Simple s2(s1);
    Simple s3;

    EXPECT_EQ(s1, s2);
    EXPECT_NE(s1, s3);
}

TEST(simple, istream)
{
    std::stringstream ss{R"(
        {
            "i": 42,
            "s": "bar",
			"d": 3.8
        }
    )"};
    Simple simple{JSON{ss}};

    EXPECT_EQ(42, simple.i);
    EXPECT_EQ(3.8, simple.d);
    EXPECT_EQ("bar", simple.s);
}
