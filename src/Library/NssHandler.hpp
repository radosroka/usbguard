#pragma once
#include <string>
#include <vector>

#include "Policy.hpp"

namespace usbguard {
	class NssHandler
	{
	public:
		NssHandler();
		~NssHandler();
		void getRuleset();
		void parseNSSwitch();

		void setNSSwitchPath(const std::string& path);
		void setPropertyName(const std::string& name);

//	private:
		std::string _prop_name;
		std::string _nsswitch_path;
		unsigned _num_possible_values;
		std::vector<std::string> _possible_values;

		Policy::SourceType _result; //default files


	};
}