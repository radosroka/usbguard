#pragma once
#include <string>

#define NUM_VALUES 3

namespace usbguard {
	class NssHandler
	{
	public:
		NssHandler();
		~NssHandler();
		static NssHandler & getNSS();
		void getRuleset();

	private:

		enum Source {
			files,
			ldap,
			sss
		};

		const std::string prop_name = "usbguard";
		const std::string nsswitch_path = "/etc/nsswitch.conf";

		const unsigned num_possible_values = NUM_VALUES;
		const std::string possible_values[NUM_VALUES] = {"files", "ldap", "sss"};

		Source result = files; //default files

		void parseNSSwitch();
	};
}