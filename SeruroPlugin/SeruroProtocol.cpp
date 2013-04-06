/*
 * Project: Seruro-NPAPI
 * File: SeruroProtocol.cpp
 * Description: Fire Breath project code to expose the Seruro API to a web browser.
 *
 * All project code (C)2012-2013 Valdrea, LLC. All rights reserved.
 *
 */

#include <boost/property_tree/json_parser.hpp>
#include <sstream>

#include "SeruroProtocol.h"

void SeruroProtocol::add(const std::string &key, const FB::variant &value)
{
	this->_data.add(key, value.convert_cast<std::string>());
}

// For debugging, returns the data section as a string.
std::string SeruroProtocol::getData()
{
	std::ostringstream output;
	boost::property_tree::write_json(output, this->_data, false);
	return output.str();
}

// For network transfer, returns a valid JOT message in binary.
void SeruroProtocol::message(unsigned char* output)
{
	// Data must be little-endian.
}

// Reads in a network transfer and parses fields.
void SeruroProtocol::load(unsigned char* input)
{

}

// Returns the _length (use after reading).
size_t SeruroProtocol::getLength()
{
	return this->_length;
}

// Reads fields, checks data consistency.
bool SeruroProtocol::isValid()
{

}

