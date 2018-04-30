#pragma once

#include "Loader.h"
#include "Submacros.h"
#include <boost/property_tree/ptree.hpp>
#include <stdexcept>

// List of derived classes for switch
#define MACRO_SINGLE_CASE_OF_DERIVED_CLASSES(r, Base, Derived) \
    if (pt.front().first == BOOST_PP_STRINGIZE(Derived)) { \
        return std::make_shared<Derived>(pt.front().second); \
    } \
    else
// end macro MACRO_SINGLE_CASE_OF_DERIVED_CLASSES

#define PRINT_CASE_LIST_OF_DERIVED_CLASSES(Base, DerivedList) \
    BOOST_PP_SEQ_FOR_EACH(MACRO_SINGLE_CASE_OF_DERIVED_CLASSES, Base, DerivedList)
// end macro PRINT_CASE_LIST_OF_DERIVED_CLASSES

// Register for polymorphic classes
#define BRAINTWISTER_RECORD_REGISTER(Base, DerivedList) \
    namespace BrainTwister { \
    namespace RecordDetails { \
    template <> \
    std::shared_ptr<Base> PolymorphicLoader<Base>::operator()(boost::property_tree::ptree const& pt) const \
    { \
        PRINT_CASE_LIST_OF_DERIVED_CLASSES(Base, DerivedList) \
        throw std::runtime_error("Derived class " + pt.front().first + " not registered for " + BOOST_PP_STRINGIZE(Base) + "."); \
        return std::shared_ptr<Base>(); \
    }}}
// end macro BRAINTWISTER_RECORD_REGISTER
