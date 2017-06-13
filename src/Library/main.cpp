#include <iostream>
#include "NssHandler.hpp"

using namespace usbguard;

int main(int argc, char const *argv[])
{
	auto x = NssHandler();
	x.parseNSSwitch();

	std::cout << x._possible_values[static_cast<unsigned>(x._result)] << std::endl;
	return 0;
}