#pragma once

#include "Loader.h"
#include "Submacros.h"
#include <boost/property_tree/ptree.hpp>
#include <string>

// Base class definition
#define BRAINTWISTER_RECORD_BASE(Name, Members, Supplements) \
    struct Name \
    { \
        typedef bool is_record; \
        typedef bool is_record_base; \
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
         : Name(markup_handler.tree) \
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
\
        Supplements \
\
    };
// end macro BRAINTWISTER_RECORD_BASE

// Base class definition with no members
// Members must be handled specially, because they can not be empty.
#define BRAINTWISTER_RECORD_BASE_NO_MEMBERS(Name, Supplements) \
    struct Name \
    { \
        typedef bool is_record; \
        typedef bool is_record_base; \
\
        virtual ~Name() {}; \
\
        virtual bool operator == (Name const& /*other*/) const \
        { \
            return true; \
        } \
\
        virtual bool operator != (Name const& /*other*/) const \
        { \
            return false; \
        } \
\
        Supplements \
\
    };
// end macro BRAINTWISTER_RECORD_BASE
