// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#include "BrainTwister/JSON.h"
#include "BrainTwister/Settings.h"
#include "BrainTwister/XML.h"
#include "gtest/gtest.h"
#include <list>
#include <map>
#include <vector>

// Test collections

BRAINTWISTER_SETTINGS(Settings2, \
    ((int, i, 0)) \
    ((double, d, 0.0)) \
    ((std::string, s, "foo")) \
)

BRAINTWISTER_SETTINGS(Settings3, \
    ((std::vector<int>, v1, std::vector<int>())) \
    ((std::vector<Settings2>, v2, std::vector<Settings2>())) \
)

BRAINTWISTER_SETTINGS(Settings4, \
    ((std::list<int>, list, std::list<int>())) \
)

//BRAINTWISTER_SETTINGS(Settings5, \
    ((std::map<int, std::string>, m1, std::map<int, std::string>())) \
)

TEST(Settings2Test, default)
{
	std::vector<Settings2> v = std::vector<Settings2>();

    EXPECT_EQ(0U, v.size());

	std::vector<Settings2> v2(v);

    EXPECT_EQ(0U, v2.size());
}

TEST(Settings2Test, default2)
{
    Settings3 settings2;

    EXPECT_EQ(0U, settings2.v1.size());
    //EXPECT_EQ(0U, settings2.v2.size());
}

TEST(Settings2Test, parameter)
{
    Settings3 settings2({8, 4, 2});

    EXPECT_EQ(8, settings2.v1[0]);
    EXPECT_EQ(4, settings2.v1[1]);
    EXPECT_EQ(2, settings2.v1[2]);

    EXPECT_EQ(0U, settings2.v2.size());
}

TEST(Settings2Test, json)
{
	Settings3 settings2{JSON{"{\"v1\": [2, 3, 1], \"v2\": [{\"i\": 3, \"d\": 3.2, \"s\": \"bar\"}]}"}};

    EXPECT_EQ(2, settings2.v1[0]);
    EXPECT_EQ(3, settings2.v1[1]);
    EXPECT_EQ(1, settings2.v1[2]);

    EXPECT_EQ(3, settings2.v2[0].i);
    EXPECT_EQ(3.2, settings2.v2[0].d);
    EXPECT_EQ("bar", settings2.v2[0].s);
}

TEST(Settings2Test, xml)
{
	Settings3 settings2{XML{"<v1><value>2</value><value>3</value><value>1</value></v1><v2><value><i>3</i><d>3.2</d><s>bar</s></value></v2>"}};

    EXPECT_EQ(2, settings2.v1[0]);
    EXPECT_EQ(3, settings2.v1[1]);
    EXPECT_EQ(1, settings2.v1[2]);

    EXPECT_EQ(3, settings2.v2[0].i);
    EXPECT_EQ(3.2, settings2.v2[0].d);
    EXPECT_EQ("bar", settings2.v2[0].s);
}

TEST(Settings2Test, std_list)
{
    Settings4 s;

    EXPECT_EQ(0U, s.list.size());
}
