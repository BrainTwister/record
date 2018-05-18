#pragma once

#include <boost/property_tree/xml_parser.hpp>
#include <sstream>
#include <string>

struct XML
{
    XML(std::string const& s)
    {
        std::istringstream iss(s);
        read_xml(iss, tree);
    }

    XML(std::istream& is)
    {
    	read_xml(is, tree);
    }

    boost::property_tree::ptree tree;
};
