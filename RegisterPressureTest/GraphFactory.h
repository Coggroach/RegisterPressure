#pragma once
#include <string>
#include <vector>

namespace DataDependence 
{
	class Graph;
	class GraphFactory
	{
	private:
		Graph* g;
	public:
		GraphFactory(int c);
		~GraphFactory();

		GraphFactory* Add(std::string name, std::vector<std::string> operands);
		Graph* Build();
	};
}



