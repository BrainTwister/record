#include "BrainTwister/JSON.h"
#include "BrainTwister/Record.h"
#include "BrainTwister/XML.h"
#include "gtest/gtest.h"
#include <string>

// Test simple types

BRAINTWISTER_RECORD(Record, \
    ((int, i, 0)) \
    ((double, d, 0.0)) \
    ((std::string, s, "foo")) \
)

TEST(Record1Test, default)
{
    Record record;

    EXPECT_EQ(0, record.i);
    EXPECT_EQ(0.0, record.d);
    EXPECT_EQ("foo", record.s);
}

TEST(Record1Test, parameter)
{
    Record record(42, 2.3);

    EXPECT_EQ(42, record.i);
    EXPECT_EQ(2.3, record.d);
}

TEST(Record1Test, builder)
{
    Record record = Record().set_i(16).set_d(3.9);

    EXPECT_EQ(16, record.i);
    EXPECT_EQ(3.9, record.d);
}

TEST(Record1Test, builder_static)
{
    static Record record = Record().set_i(16).set_d(3.9);

    EXPECT_EQ(16, record.i);
    EXPECT_EQ(3.9, record.d);
}

TEST(Record1Test, copy_constructor)
{
    Record s1(42, 2.3);
    Record s2(s1);

    EXPECT_EQ(42, s2.i);
    EXPECT_EQ(2.3, s2.d);
}

TEST(Record1Test, copy_operator)
{
    Record s1 = Record().set_i(16).set_d(3.9).set_s("bar");
    Record s2 = s1;

    EXPECT_EQ(16, s2.i);
    EXPECT_EQ(3.9, s2.d);
    EXPECT_EQ("bar", s2.s);
}

TEST(Record1Test, ptree)
{
    boost::property_tree::ptree pt;
    pt.put("i", "42");
    pt.put("d", "2.3");
    Record record(pt);

    EXPECT_EQ(42, record.i);
    EXPECT_EQ(2.3, record.d);
}

TEST(Record1Test, json)
{
	Record record{JSON{"{\"i\": 42, \"d\": 3.8, \"s\": \"bar\"}"}};

    EXPECT_EQ(42, record.i);
    EXPECT_EQ(3.8, record.d);
    EXPECT_EQ("bar", record.s);
}

TEST(Record1Test, json_unordered)
{
	Record record{JSON{"{\"s\": \"bar\", \"i\": 42, \"d\": 3.8}"}};

    EXPECT_EQ(42, record.i);
    EXPECT_EQ(3.8, record.d);
    EXPECT_EQ("bar", record.s);
}

TEST(Record1Test, json_default)
{
	Record record{JSON{"{\"i\": 42}"}};

    EXPECT_EQ(42, record.i);
    EXPECT_EQ(0.0, record.d);
    EXPECT_EQ("foo", record.s);
}

TEST(Record1Test, xml)
{
	Record record{XML{"<i>42</i><d>3.8</d><s>bar</s>"}};

    EXPECT_EQ(42, record.i);
    EXPECT_EQ(3.8, record.d);
    EXPECT_EQ("bar", record.s);
}

TEST(Record1Test, xml_unordered)
{
	Record record{XML{"<s>bar</s><i>42</i><d>3.8</d>"}};

    EXPECT_EQ(42, record.i);
    EXPECT_EQ(3.8, record.d);
    EXPECT_EQ("bar", record.s);
}

TEST(Record1Test, xml_default)
{
	Record record{XML{"<i>42</i>"}};

    EXPECT_EQ(42, record.i);
    EXPECT_EQ(0.0, record.d);
    EXPECT_EQ("foo", record.s);
}

TEST(Record1Test, compare)
{
    Record s1(42, 2.3);
    Record s2(s1);
    Record s3;

    EXPECT_EQ(s1, s2);
    EXPECT_NE(s1, s3);
}
