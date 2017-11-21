// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BrainTwister
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#include "BrainTwister/JSON.h"
#include "BrainTwister/Settings.h"
#include "BrainTwister/XML.h"
#include "gtest/gtest.h"
#include <string>

// Test simple types

BRAINTWISTER_SETTINGS(Settings, \
    ((int, i, 0)) \
    ((double, d, 0.0)) \
    ((std::string, s, "foo")) \
)

TEST(Settings1Test, default)
{
    Settings settings;

    EXPECT_EQ(0, settings.i);
    EXPECT_EQ(0.0, settings.d);
    EXPECT_EQ("foo", settings.s);
}

TEST(Settings1Test, parameter)
{
    Settings settings(42, 2.3);

    EXPECT_EQ(42, settings.i);
    EXPECT_EQ(2.3, settings.d);
}

TEST(Settings1Test, builder)
{
    Settings settings = Settings().set_i(16).set_d(3.9);

    EXPECT_EQ(16, settings.i);
    EXPECT_EQ(3.9, settings.d);
}

TEST(Settings1Test, builder_static)
{
    static Settings settings = Settings().set_i(16).set_d(3.9);

    EXPECT_EQ(16, settings.i);
    EXPECT_EQ(3.9, settings.d);
}

TEST(Settings1Test, copy)
{
    Settings s1(42, 2.3);
    Settings s2(s1);

    EXPECT_EQ(42, s2.i);
    EXPECT_EQ(2.3, s2.d);
}

TEST(Settings1Test, ptree)
{
    boost::property_tree::ptree pt;
    pt.put("i", "42");
    pt.put("d", "2.3");
    Settings settings(pt);

    EXPECT_EQ(42, settings.i);
    EXPECT_EQ(2.3, settings.d);
}

TEST(Settings1Test, json)
{
	Settings settings{JSON{"{\"i\": 42, \"d\": 3.8, \"s\": \"bar\"}"}};

    EXPECT_EQ(42, settings.i);
    EXPECT_EQ(3.8, settings.d);
    EXPECT_EQ("bar", settings.s);
}

TEST(Settings1Test, json_unordered)
{
	Settings settings{JSON{"{\"s\": \"bar\", \"i\": 42, \"d\": 3.8}"}};

    EXPECT_EQ(42, settings.i);
    EXPECT_EQ(3.8, settings.d);
    EXPECT_EQ("bar", settings.s);
}

TEST(Settings1Test, json_default)
{
	Settings settings{JSON{"{\"i\": 42}"}};

    EXPECT_EQ(42, settings.i);
    EXPECT_EQ(0.0, settings.d);
    EXPECT_EQ("foo", settings.s);
}

TEST(Settings1Test, xml)
{
	Settings settings{XML{"<i>42</i><d>3.8</d><s>bar</s>"}};

    EXPECT_EQ(42, settings.i);
    EXPECT_EQ(3.8, settings.d);
    EXPECT_EQ("bar", settings.s);
}

TEST(Settings1Test, xml_unordered)
{
	Settings settings{XML{"<s>bar</s><i>42</i><d>3.8</d>"}};

    EXPECT_EQ(42, settings.i);
    EXPECT_EQ(3.8, settings.d);
    EXPECT_EQ("bar", settings.s);
}

TEST(Settings1Test, xml_default)
{
	Settings settings{XML{"<i>42</i>"}};

    EXPECT_EQ(42, settings.i);
    EXPECT_EQ(0.0, settings.d);
    EXPECT_EQ("foo", settings.s);
}

TEST(Settings1Test, compare)
{
    Settings s1(42, 2.3);
    Settings s2(s1);
    Settings s3;

    EXPECT_EQ(s1, s2);
    EXPECT_NE(s1, s3);
}
