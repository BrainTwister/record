#pragma once

#include "Submacros.h"
#include "SettingsDetails.h"
#include <boost/property_tree/ptree.hpp>

// Class definition
#define BRAINTWISTER_SETTINGS(Name, Members) \
    struct Name \
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
        template <class MarkupHandler> \
        Name(MarkupHandler const& markup_handler) \
		 : Name(markup_handler.get_ptree()) \
        {} \
\
        bool operator == (Name const& other) const \
        { \
            return PRINT_COMPARE_ARGUMENTS(Members); \
        } \
\
        bool operator != (Name const& other) const \
        { \
            return !operator == (other); \
        } \
\
        PRINT_CLASS_MEMBER_SETTERS(Name, Members) \
\
        PRINT_CLASS_MEMBERS(Members) \
    };
// end macro BRAINTWISTER_SETTINGS
