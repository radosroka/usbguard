#include "NssHandler.hpp"
#include "Exception.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#define MIN_LENGTH 14 //length of "usbguard: sss", shortest possible configuration

namespace usbguard {

	NssHandler::NssHandler()
	{

		this->parseNSSwitch();
	}

	NssHandler::~NssHandler()
	{

	}

	NssHandler & NssHandler::getNSS()
	{
		/*if(!NssHandler::nss_handler)
			NssHandler::nss_handler = new NssHandler();
		return NssHandler::nss_handler;*/
		static NssHandler INSTANCE;
		return INSTANCE;
	}

	void NssHandler::getRuleset()
	{

	}

	void NssHandler::parseNSSwitch()
	{
		std::ifstream nss(this->nsswitch_path);
		bool found = false;

		if (!nss.is_open()) {
			throw ErrnoException("NSSwitch parsing", this->nsswitch_path, errno);
    	}

    	std::string line;

    	while(std::getline(nss, line)) {
    		
    		if(line.length() < MIN_LENGTH || line[0] == '#')
    			continue;

    		unsigned index = 0;
    		int res = 0;
    		if((res = line.find(this->prop_name)) < 0)
    			continue;
    		else {
    			index = (unsigned)res + this->prop_name.length();

    			bool line_end = false;

    			while(isspace(line[index]))
    			{
    				if(index >= line.length())
    				{
    					line_end = true;
    					break;
    				}

    				index++;
    			}

    			if(line_end) continue;

    			if(line[index] != ':')
    				continue;
    			else 
    				index++;

    			while(isspace(line[index]))
    			{
    				if(index >= line.length())
    				{
    					line_end = true;
    					break;
    				}

    				index++;
    			}

    			if(line_end) continue;

    			std::string result;

    			while(!isspace(line[index]))
    			{
    				if(index >= line.length())
    					break;

    				result.push_back(line[index]);
    				index++;
    			}

    			for(unsigned i = 0 ; i < this->num_possible_values ; i++)
    			{
    				if(result == this->possible_values[i])
    				{
    					this->result = static_cast<Source>(i);
    					found = true;
    				}
    			}

    			if(!found)
    				std::cout << "Parsed nsswitch.conf property is not supported -- " << "\"" << result << "\"" << std::endl;

    		}
    	}

    	/*
    	*	need to rewrite to usbguard log interface
    	*/

    	if(found)
    	{
    		std::cout << "Parsed nsswitch.conf succesfully -- " << "\"" << this->possible_values[result] << "\"" << std::endl;
    	}
    	else {
    		std::cout << "Parsed nsswitch.conf unsuccesfully. Using default -- " << "\"" << this->possible_values[result] << "\"" << std::endl;
    	}

		nss.close();
	}
}