#include "BrainTwister/JSON.h"
#include "BrainTwister/XML.h"
#include "collections.h"
#include "gtest/gtest.h"

// types with two arguments std::map<int, int> will not work,
// because of the comma in-between the brackets interpreted as multiple macro arguments.

TEST(collections, vector_of_record)
{
    std::vector<Collection1> v = std::vector<Collection1>();

    EXPECT_EQ(0U, v.size());

    std::vector<Collection1> v2(v);

    EXPECT_EQ(0U, v2.size());
}

TEST(collections, default)
{
    Collection2 collection;

    EXPECT_EQ(0U, collection.v1.size());
    EXPECT_EQ(0U, collection.v2.size());
}

TEST(collections, parameter)
{
    Collection2 collection({8, 4, 2});

    EXPECT_EQ(8, collection.v1[0]);
    EXPECT_EQ(4, collection.v1[1]);
    EXPECT_EQ(2, collection.v1[2]);

    EXPECT_EQ(0U, collection.v2.size());
}

TEST(collections, json)
{
    Collection2 collection{JSON{R"(
        {
            "v1": [2, 3, 1],
            "v2": [{
                "i": 3,
                "d": 3.2,
                "s": "bar"
            },
            {
                "i": 42,
                "d": 4.7,
                "s": "foo"
            }]
        }
    )"}};

    EXPECT_EQ(2, collection.v1[0]);
    EXPECT_EQ(3, collection.v1[1]);
    EXPECT_EQ(1, collection.v1[2]);

    EXPECT_EQ(3, collection.v2[0].i);
    EXPECT_EQ(3.2, collection.v2[0].d);
    EXPECT_EQ("bar", collection.v2[0].s);

    EXPECT_EQ(42, collection.v2[1].i);
    EXPECT_EQ(4.7, collection.v2[1].d);
    EXPECT_EQ("foo", collection.v2[1].s);
}

TEST(collections, xml)
{
    Collection2 collection{XML{R"(
        <v1>
             <value>2</value>
             <value>3</value>
             <value>1</value>
        </v1>
        <v2>
             <value>
                 <i>3</i>
                 <d>3.2</d>
                 <s>bar</s>
             </value>
             <value>
                 <i>42</i>
                 <d>4.7</d>
                 <s>foo</s>
             </value>
        </v2>
    )"}};

    EXPECT_EQ(2, collection.v1[0]);
    EXPECT_EQ(3, collection.v1[1]);
    EXPECT_EQ(1, collection.v1[2]);

    EXPECT_EQ(3, collection.v2[0].i);
    EXPECT_EQ(3.2, collection.v2[0].d);
    EXPECT_EQ("bar", collection.v2[0].s);

    EXPECT_EQ(42, collection.v2[1].i);
    EXPECT_EQ(4.7, collection.v2[1].d);
    EXPECT_EQ("foo", collection.v2[1].s);
}

TEST(collections, list)
{
    Collection3 collection;

    EXPECT_EQ(0U, collection.list.size());
}
