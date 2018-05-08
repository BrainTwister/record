#include "BrainTwister/JSON.h"
#include "BrainTwister/Record.h"
#include "BrainTwister/XML.h"
#include "gtest/gtest.h"
#include <memory>
#include <vector>

// Test pointer

BRAINTWISTER_RECORD(Record7, \
    ((std::shared_ptr<int>, ptr_i, std::shared_ptr<int>())) \
)

TEST(Record4Test, default)
{
    Record7 record;

    EXPECT_EQ(std::shared_ptr<int>(), record.ptr_i);
}

TEST(Record4Test, parameter)
{
    auto ptr_i = std::make_shared<int>(4);
    Record7 record4(ptr_i);

    EXPECT_EQ(4, *record4.ptr_i);
}

TEST(Record4Test, json)
{
    Record7 record4{JSON{"{\"ptr_i\": 4}"}};

    EXPECT_EQ(4, *record4.ptr_i);
}
