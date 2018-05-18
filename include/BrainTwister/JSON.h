#pragma once

#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include <string>

struct JSON
{
    JSON(std::string const& s)
    {
        std::istringstream iss(s);
        read_json(iss, tree);
    }

    JSON(std::istream& is)
    {
    	read_json(is, tree);
    }

    boost::property_tree::ptree tree;
};
