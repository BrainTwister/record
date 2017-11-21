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
#include <memory>
#include <vector>

// Test pointer

BRAINTWISTER_SETTINGS(Settings4, \
    ((std::shared_ptr<int>, ptr_i, std::shared_ptr<int>())) \
)

TEST(Settings4Test, default)
{
    Settings4 settings;

    EXPECT_EQ(std::shared_ptr<int>(), settings.ptr_i);
}

TEST(Settings4Test, parameter)
{
    auto ptr_i = std::make_shared<int>(4);
    Settings4 settings4(ptr_i);

    EXPECT_EQ(4, *settings4.ptr_i);
}

TEST(Settings4Test, json)
{
	Settings4 settings4{JSON{"{\"ptr_i\": 4}"}};

    EXPECT_EQ(4, *settings4.ptr_i);
}
