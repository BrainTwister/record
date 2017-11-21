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

BRAINTWISTER_SETTINGS(Settings4, \
    ((int, i, 3)) \
    ((double, d, 2.7)) \
)

BRAINTWISTER_SETTINGS(Settings5, \
    ((int, i, 5)) \
    ((Settings4, settings1, Settings4{})) \
)

BRAINTWISTER_SETTINGS(Settings6, \
    ((int, i, 7)) \
    ((Settings4, settings1, Settings4{}.set_i(125).set_d(30.7))) \
)

//TEST(Settings3Test, is_setting)
//{
//    EXPECT_FALSE(BrainTwister::SettingsDetails::is_setting<int>::value);
//    EXPECT_TRUE(BrainTwister::SettingsDetails::is_setting<Settings4>::value);
//    EXPECT_TRUE(BrainTwister::SettingsDetails::is_setting<Settings5>::value);
//    EXPECT_TRUE(BrainTwister::SettingsDetails::is_setting<Settings6>::value);
//}

TEST(Settings3Test, default1)
{
    Settings4 settings1;

    EXPECT_EQ(3, settings1.i);
    EXPECT_EQ(2.7, settings1.d);
}

TEST(Settings3Test, default2)
{
    Settings5 settings2;

    EXPECT_EQ(5, settings2.i);
    EXPECT_EQ(3, settings2.settings1.i);
    EXPECT_EQ(2.7, settings2.settings1.d);
}

TEST(Settings3Test, default3)
{
    Settings6 settings3;

    EXPECT_EQ(7, settings3.i);
    EXPECT_EQ(125, settings3.settings1.i);
    EXPECT_EQ(30.7, settings3.settings1.d);
}

TEST(Settings3Test, GenericLoader_int)
{
    boost::property_tree::ptree tree;
    tree.put("i", "42");
    auto i = BrainTwister::SettingsDetails::GenericLoader<int>()(tree, "i", 5);

    EXPECT_EQ(42, i);
}

TEST(Settings3Test, GenericLoader_settings)
{
    boost::property_tree::ptree leaf;
    leaf.put("i", "1");
    leaf.put("d", "2.5");
    boost::property_tree::ptree tree;
    tree.add_child("settings1", leaf);
    auto settings1 = BrainTwister::SettingsDetails::GenericLoader<Settings4>()(tree, "settings1", Settings4());

    EXPECT_EQ(1, settings1.i);
}

TEST(Settings3Test, json1)
{
    auto json = JSON{"{\"i\": 42, \"settings1\": {\"i\": 33, \"d\": 3.8}}"};
    auto i = BrainTwister::SettingsDetails::GenericLoader<int>()(json.get_ptree(), "i", 0);
    auto settings1 = BrainTwister::SettingsDetails::GenericLoader<Settings4>()(json.get_ptree(), "settings1", Settings4());

    EXPECT_EQ(42, i);
    EXPECT_EQ(33, settings1.i);
    EXPECT_EQ(3.8, settings1.d);
}

TEST(Settings3Test, json2)
{
    auto json = JSON{"{\"i\": 42, \"settings1\": {\"i\": 33, \"d\": 3.8}}"};
    auto settings2 = Settings5(json.get_ptree());

    EXPECT_EQ(42, settings2.i);
    EXPECT_EQ(33, settings2.settings1.i);
    EXPECT_EQ(3.8, settings2.settings1.d);
}

TEST(Settings3Test, json3)
{
    Settings5 settings2{JSON{"{\"i\": 42, \"settings1\": {\"i\": 33, \"d\": 3.8}}"}};

    EXPECT_EQ(42, settings2.i);
    EXPECT_EQ(33, settings2.settings1.i);
    EXPECT_EQ(3.8, settings2.settings1.d);
}

TEST(Settings3Test, xml)
{
    Settings5 settings2{XML{"<i>42</i><settings1><i>33</i><d>3.8</d></settings1>"}};

    EXPECT_EQ(42, settings2.i);
    EXPECT_EQ(33, settings2.settings1.i);
    EXPECT_EQ(3.8, settings2.settings1.d);
}
