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
        Name(PRINT_CONSTRUCTOR_ARGUMENTS(Members)) noexcept \
         : PRINT_INITIALIZE_ARGUMENTS(Members) \
        {} \
\
        Name(Name const& other) noexcept \
         : PRINT_COPY_ARGUMENTS(Members) \
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
        virtual ~Name() {}; \
\
        virtual bool operator == (Name const& other) const \
        { \
            return PRINT_COMPARE_ARGUMENTS(Members); \
        } \
\
        virtual bool operator != (Name const& other) const \
        { \
            return !operator == (other); \
        } \
\
        PRINT_CLASS_MEMBERS(Members) \
    };
// end macro BRAINTWISTER_SETTINGS
