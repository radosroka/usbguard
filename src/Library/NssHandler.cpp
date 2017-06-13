#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

#include "NssHandler.hpp"
#include "Exception.hpp"
#include "Logger.hpp"

#define MIN_LENGTH 14 //length of "usbguard: sss", shortest possible configuration
#define NUM_VALUES 3

namespace usbguard {

	NssHandler::NssHandler()
        :   _prop_name("usbguard"),
            _nsswitch_path("/etc/nsswitch.conf"),            
            _possible_values({"files", "ldap", "sss"})
            
	{
        _num_possible_values = _possible_values.size();
        _result = Policy::SourceType::Local;
	}

    NssHandler::~NssHandler()
    {

    }


    void NssHandler::setNSSwitchPath(const String& path)
    {
        _nsswitch_path = path;
    }

    void NssHandler::setPropertyName(const String& name)
    {
        _prop_name = name;
    }

	void NssHandler::getRuleset()
	{

	}

	void NssHandler::parseNSSwitch()
	{
		std::ifstream nss(this->_nsswitch_path);
		bool found = false;

		if (!nss.is_open()) {
			throw ErrnoException("NSSwitch parsing", this->_nsswitch_path, errno);
    	}

    	std::string line;

    	while(std::getline(nss, line)) {
    		
    		if(line.length() < MIN_LENGTH || line[0] == '#')
    			continue;

    		unsigned index = 0;
    		int res = 0;
    		if((res = line.find(this->_prop_name)) < 0)
    			continue;
    		else {
    			index = (unsigned)res + this->_prop_name.length();

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

    			for(unsigned i = 0 ; i < this->_num_possible_values ; i++)
    			{
    				if(result == this->_possible_values[i])
    				{
    					this->_result = static_cast<Policy::SourceType>(i);
    					found = true;
    				}
    			}

    			if(!found)
    				USBGUARD_LOG(Info) << "Parsed nsswitch.conf property is not supported -- " << "\"" << result << "\"" << std::endl;

    		}
    	}

    	/*
    	*	need to rewrite to usbguard log interface
    	*/

    	if(found)
    	{
    		USBGUARD_LOG(Info) << "Parsed nsswitch.conf succesfully -- " << "\"" << _possible_values[static_cast<unsigned>(_result)] << "\"" << std::endl;
    	}
    	else {
    		USBGUARD_LOG(Info) << "Parsed nsswitch.conf unsuccesfully. Using default -- " << "\"" << _possible_values[static_cast<unsigned>(_result)] << "\"" << std::endl;
    	}

		nss.close();
	}
}