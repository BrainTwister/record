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
#include <vector>

// Test nested structures

BRAINTWISTER_SETTINGS(Settings1, \
    ((int, i, 3)) \
    ((double, d, 2.7)) \
)

BRAINTWISTER_SETTINGS(Settings2, \
    ((int, i, 5)) \
    ((Settings1, settings1, Settings1{})) \
)

BRAINTWISTER_SETTINGS(Settings3, \
    ((int, i, 7)) \
    ((Settings1, settings1, Settings1().set_i(125).set_d(30.7))) \
)

TEST(Settings3Test, default1)
{
	Settings1 settings1;

    EXPECT_EQ(3, settings1.i);
    EXPECT_EQ(2.7, settings1.d);
}

//TEST(Settings3Test, default2)
//{
//	Settings2 settings2;
//
//    EXPECT_EQ(5, settings2.i);
//    EXPECT_EQ(3, settings2.settings1.i);
//    EXPECT_EQ(2.7, settings2.settings1.d);
//}

TEST(Settings3Test, default3)
{
	Settings3 settings3;

    EXPECT_EQ(7, settings3.i);
    EXPECT_EQ(125, settings3.settings1.i);
    EXPECT_EQ(30.7, settings3.settings1.d);
}

TEST(Settings3Test, json)
{
	Settings2 settings2{JSON{"{\"i\": 42, \"settings1\": {\"i\": 33, \"d\": 3.8}}"}};

    EXPECT_EQ(42, settings2.i);
    EXPECT_EQ(33, settings2.settings1.i);
    EXPECT_EQ(3.8, settings2.settings1.d);
}

TEST(Settings3Test, xml)
{
	Settings2 settings2{XML{"<i>42</i><settings1><i>33</i><d>3.8</d></settings1>"}};

    EXPECT_EQ(42, settings2.i);
    EXPECT_EQ(33, settings2.settings1.i);
    EXPECT_EQ(3.8, settings2.settings1.d);
}
