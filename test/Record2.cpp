// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#include "BrainTwister/JSON.h"
#include "BrainTwister/Record.h"
#include "BrainTwister/XML.h"
#include "gtest/gtest.h"
#include <list>
#include <map>
#include <vector>

// Test collections

BRAINTWISTER_RECORD(Record2, \
    ((int, i, 0)) \
    ((double, d, 0.0)) \
    ((std::string, s, "foo")) \
)

BRAINTWISTER_RECORD(Record3, \
    ((std::vector<int>, v1, std::vector<int>())) \
    ((std::vector<Record2>, v2, std::vector<Record2>())) \
)

BRAINTWISTER_RECORD(Record4, \
    ((std::list<int>, list, std::list<int>())) \
)

// templates with more than 2 arguments std::map<int, int> will not work,
// because of the comma in-between the brackets interpreted as multiple macro arguments.

TEST(Record2Test, default)
{
	std::vector<Record2> v = std::vector<Record2>();

    EXPECT_EQ(0U, v.size());

	std::vector<Record2> v2(v);

    EXPECT_EQ(0U, v2.size());
}

TEST(Record2Test, default2)
{
    Record3 record2;

    EXPECT_EQ(0U, record2.v1.size());
    //EXPECT_EQ(0U, record2.v2.size());
}

TEST(Record2Test, parameter)
{
    Record3 record2({8, 4, 2});

    EXPECT_EQ(8, record2.v1[0]);
    EXPECT_EQ(4, record2.v1[1]);
    EXPECT_EQ(2, record2.v1[2]);

    EXPECT_EQ(0U, record2.v2.size());
}

TEST(Record2Test, json)
{
	Record3 record2{JSON{"{\"v1\": [2, 3, 1], \"v2\": [{\"i\": 3, \"d\": 3.2, \"s\": \"bar\"}]}"}};

    EXPECT_EQ(2, record2.v1[0]);
    EXPECT_EQ(3, record2.v1[1]);
    EXPECT_EQ(1, record2.v1[2]);

    EXPECT_EQ(3, record2.v2[0].i);
    EXPECT_EQ(3.2, record2.v2[0].d);
    EXPECT_EQ("bar", record2.v2[0].s);
}

TEST(Record2Test, xml)
{
	Record3 record2{XML{"<v1><value>2</value><value>3</value><value>1</value></v1><v2><value><i>3</i><d>3.2</d><s>bar</s></value></v2>"}};

    EXPECT_EQ(2, record2.v1[0]);
    EXPECT_EQ(3, record2.v1[1]);
    EXPECT_EQ(1, record2.v1[2]);

    EXPECT_EQ(3, record2.v2[0].i);
    EXPECT_EQ(3.2, record2.v2[0].d);
    EXPECT_EQ("bar", record2.v2[0].s);
}

TEST(Record2Test, std_list)
{
    Record4 s;

    EXPECT_EQ(0U, s.list.size());
}
