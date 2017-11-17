#pragma once

#include "SettingsDetails.h"
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// Initialization list of default constructor
#define MACRO_SINGLE_INITIALIZE_DEFAULT(r,size,i,elem) \
    BOOST_PP_TUPLE_ELEM(3,1,elem)(BOOST_PP_TUPLE_ELEM(3,2,elem)) BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_INITIALIZE_DEFAULT(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_INITIALIZE_DEFAULT,BOOST_PP_SEQ_SIZE(SEQ),SEQ)

// Initialization list of parameter constructor
#define MACRO_SINGLE_INITIALIZE_ARGUMENTS(r,size,i,elem) \
    BOOST_PP_TUPLE_ELEM(3,1,elem)(BOOST_PP_TUPLE_ELEM(3,1,elem)) BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_INITIALIZE_ARGUMENTS(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_INITIALIZE_ARGUMENTS,BOOST_PP_SEQ_SIZE(SEQ),SEQ)

// List of arguments of parameter constructor
#define MACRO_SINGLE_CONSTRUCTOR_ARGUMENT(r,size,i,elem) \
    BOOST_PP_TUPLE_ELEM(3,0,elem) BOOST_PP_TUPLE_ELEM(3,1,elem) = BOOST_PP_TUPLE_ELEM(3,2,elem) \
    BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_CONSTRUCTOR_ARGUMENTS(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_CONSTRUCTOR_ARGUMENT,BOOST_PP_SEQ_SIZE(SEQ),SEQ)

// List of arguments of copy constructor
#define MACRO_SINGLE_COPY_ARGUMENTS(r, size, i, elem) \
    BOOST_PP_TUPLE_ELEM(3,1,elem)(other. BOOST_PP_TUPLE_ELEM(3,1,elem)) BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_COPY_ARGUMENTS(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_COPY_ARGUMENTS, BOOST_PP_SEQ_SIZE(SEQ), SEQ)

// List of arguments for comparison
#define MACRO_SINGLE_COMPARE_ARGUMENTS(r, size, i, elem) \
    BOOST_PP_TUPLE_ELEM(3,1,elem) == other. BOOST_PP_TUPLE_ELEM(3,1,elem) BOOST_PP_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1),&&,)

#define PRINT_COMPARE_ARGUMENTS(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_COMPARE_ARGUMENTS, BOOST_PP_SEQ_SIZE(SEQ), SEQ)

// List of class members
#define MACRO_SINGLE_MEMBER(r,data,elem) \
    BOOST_PP_TUPLE_ELEM(3,0,elem) BOOST_PP_TUPLE_ELEM(3,1,elem);

#define PRINT_CLASS_MEMBERS(SEQ) \
    BOOST_PP_SEQ_FOR_EACH(MACRO_SINGLE_MEMBER,,SEQ)

// List of arguments for loading by boost property tree
#define MACRO_SINGLE_MEMBER_LOAD(r, size, i, elem) \
    BOOST_PP_TUPLE_ELEM(3,1,elem)( ::BrainTwister::SettingsDetails::GenericLoader<BOOST_PP_TUPLE_ELEM(3,0,elem)>()(tree, \
    BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3,1,elem)), BOOST_PP_TUPLE_ELEM(3,2,elem))) \
    BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_CLASS_MEMBERS_LOAD(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_MEMBER_LOAD, BOOST_PP_SEQ_SIZE(SEQ), SEQ)

// Serialization
#define MACRO_SINGLE_MEMBER_SERIALIZATION(r, data, elem) \
    ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3,1,elem)), BOOST_PP_TUPLE_ELEM(3,1,elem));

#define PRINT_CLASS_MEMBERS_SERIALIZATION(SEQ) \
    BOOST_PP_SEQ_FOR_EACH(MACRO_SINGLE_MEMBER_SERIALIZATION,,SEQ)
