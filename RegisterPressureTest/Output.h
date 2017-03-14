#pragma once
#include <string>
#include <vector>
#include "Vertex.h"

namespace Output
{
	void WriteLine(std::string);
	void WriteLine(std::vector<std::string>);
	std::string ReadLine();
	void WriteLine(std::string, std::vector<DataDependence::Vertex*>);
};

