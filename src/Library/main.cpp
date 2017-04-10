#include <iostream>
#include "NssHandler.hpp"

using namespace usbguard;

int main(int argc, char const *argv[])
{
	NssHandler::getNSS();
	NssHandler::getNSS();
	NssHandler::getNSS();
	NssHandler::getNSS();
	NssHandler::getNSS();

//	std::cout << nss.possible_values[nss.result] << std::endl;
	return 0;
}