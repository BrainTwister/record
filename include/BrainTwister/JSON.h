#pragma once

#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include <string>

struct JSON
{
	JSON(std::string const& json_string)
	 : json_string(json_string)
	{};

	boost::property_tree::ptree get_ptree() const
	{
	    std::stringstream ss{json_string};
	    boost::property_tree::ptree tree;
	    read_json(ss, tree);
	    return tree;
	}

	std::string json_string;
};
