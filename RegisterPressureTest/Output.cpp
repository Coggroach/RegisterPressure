#include "Output.h"
#include <iostream>

void Output::WriteLine(std::string s)
{
	std::cout << s << std::endl;
}

void Output::WriteLine(std::vector<std::string> s)
{
	for (auto i : s)
		std::cout << i << " ";
	std::cout << std::endl;
}

std::string Output::ReadLine()
{
	std::string s;
	std::cin >> s;
	return s;
}
