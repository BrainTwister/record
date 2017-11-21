// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BrainTwister
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#include "BrainTwister/JSON.h"
#include "BrainTwister/Settings.h"
#include "BrainTwister/SettingsBase.h"
#include "BrainTwister/SettingsDerived.h"
#include "BrainTwister/SettingsRegister.h"
#include "BrainTwister/XML.h"
#include "gtest/gtest.h"
#include <memory>
#include <string>

// Test polymorphism

BRAINTWISTER_SETTINGS_BASE(SettingsBase, \
    ((std::string, s1, "base")), \
	virtual double operator ()() const = 0; \
)

BRAINTWISTER_SETTINGS_DERIVED(SettingsDerived1, SettingsBase, \
    ((int, i, 4)) \
    ((std::string, s2, "foo")), \
	virtual double operator ()() const { return i; } \
)

BRAINTWISTER_SETTINGS_DERIVED(SettingsDerived2, SettingsBase, \
    ((double, d, 2.3)) \
    ((std::string, s3, "bar")), \
	virtual double operator ()() const { return d; } \
)

BRAINTWISTER_SETTINGS_REGISTER(SettingsBase, \
    (SettingsDerived1) \
    (SettingsDerived2) \
)

BRAINTWISTER_SETTINGS(Settings8, \
    ((std::shared_ptr<SettingsBase>, p1, std::shared_ptr<SettingsBase>())) \
    ((std::shared_ptr<SettingsBase>, p2, std::shared_ptr<SettingsDerived1>())) \
)

TEST(Settings5Test, default)
{
    Settings8 settings;

    EXPECT_EQ(std::shared_ptr<SettingsBase>(), settings.p1);
    EXPECT_EQ(std::shared_ptr<SettingsDerived1>(), settings.p2);
}

TEST(Settings5Test, parameter_constructor)
{
    std::shared_ptr<SettingsBase> p1{new SettingsDerived1{4}};
    Settings8 settings(p1);

    EXPECT_EQ(4, std::dynamic_pointer_cast<SettingsDerived1>(settings.p1)->i);
}

TEST(Settings5Test, json)
{
	Settings8 settings5{JSON{"{\"p1\": {\"SettingsDerived1\": {\"i\": 42}}}"}};

    EXPECT_EQ(42, std::dynamic_pointer_cast<SettingsDerived1>(settings5.p1)->i);
}

TEST(Settings5Test, json2)
{
	Settings8 settings5{JSON{"{\"p1\": {\"SettingsDerived1\": {\"i\": 42}}, \"p2\": {\"SettingsDerived2\": {\"d\": 3.9}}}"}};

    EXPECT_EQ(42, std::dynamic_pointer_cast<SettingsDerived1>(settings5.p1)->i);
    EXPECT_EQ(3.9, std::dynamic_pointer_cast<SettingsDerived2>(settings5.p2)->d);

    EXPECT_EQ(42, settings5.p1->operator()());
}
