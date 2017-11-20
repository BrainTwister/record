#pragma once

#include <boost/property_tree/xml_parser.hpp>
#include <sstream>
#include <string>

struct XML
{
	XML(std::string const& xml_string)
	 : xml_string(xml_string)
	{};

	boost::property_tree::ptree get_ptree() const
	{
	    std::stringstream ss{xml_string};
	    boost::property_tree::ptree tree;
	    read_xml(ss, tree);
	    return tree;
	}

	std::string xml_string;
};
