#include "BrainTwister/JSON.h"
#include "BrainTwister/XML.h"
#include "gtest/gtest.h"
#include "pointer.h"

TEST(pointer, default)
{
    Pointer pointer;

    EXPECT_EQ(42, *pointer.p);
}

TEST(pointer, parameter)
{
    auto p = std::make_shared<int>(4);
    Pointer pointer(p);

    EXPECT_EQ(4, *pointer.p);
}

TEST(pointer, builder)
{
    auto pointer = Pointer().set_p(std::make_shared<int>(4));

    EXPECT_EQ(4, *pointer.p);
}

TEST(pointer, json)
{
    Pointer pointer{JSON{R"(
        {
            "p": 4
        }
    )"}};

    EXPECT_EQ(4, *pointer.p);
}

TEST(pointer, xml)
{
    Pointer pointer(XML("<p>4</p>"));

    EXPECT_EQ(4, *pointer.p);
}
