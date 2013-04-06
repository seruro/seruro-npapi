/*
 * Project: Seruro-NPAPI
 * File: SeruroProtocol.h
 * Description: Fire Breath project code to expose the Seruro API to a web browser.
 *
 * All project code (C)2012-2013 Valdrea, LLC. All rights reserved.
 *
 */

#include <boost/property_tree/ptree.hpp>

#include "JSAPIAuto.h"

#include "SeruroPlugin.h"

#ifndef H_SeruroProtocol
#define H_SeruroProtocol

class SeruroProtocol
{
public:
	SeruroProtocol() : _id(203), _length(0) {}

	void add(const std::string &key, const FB::variant &value);

	std::string getData();

	void message(unsigned char* output);
	void load(unsigned char* input);

	size_t getLength();
	bool isValid();

private:
	unsigned short _id;
	size_t _length;
	boost::property_tree::ptree _data;
};

#endif
