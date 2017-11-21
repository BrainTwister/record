#pragma once

#include "Submacros.h"
#include "SettingsDetails.h"
#include <boost/property_tree/ptree.hpp>
#include <string>

// Derived class definition
#define BRAINTWISTER_SETTINGS_DERIVED(Name, Base, Members, Supplements) \
    struct Name : Base \
    { \
        typedef bool is_setting; \
\
        Name(PRINT_CONSTRUCTOR_ARGUMENTS(Members)) \
         : PRINT_INITIALIZE_ARGUMENTS(Members) \
        {} \
\
        Name(boost::property_tree::ptree const& tree) \
         : PRINT_CLASS_MEMBERS_LOAD(Members) \
        {} \
\
        virtual ~Name() {}; \
\
        virtual bool operator == (Base const& other) const \
        { \
            if (!Base::operator == (other)) return false; \
            return true; \
            /** return PRINT_COMPARE_ARGUMENTS(Members); **/ \
        } \
\
        virtual bool operator != (Base const& other) const \
        { \
            return !operator == (other); \
        } \
\
        PRINT_CLASS_MEMBERS(Members) \
\
        Supplements \
\
    };
// end macro BRAINTWISTER_SETTINGS_DERIVED
