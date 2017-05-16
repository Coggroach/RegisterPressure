#pragma once
#include <vector>

namespace DataDependence
{
	class Graph;
	class Graphs
	{
	public:

		static Graph* Diamond();
		static Graph* Droplets();
		static Graph* Mirror();
		static Graph* Parallel();
		static Graph* Rombus();
		static Graph* Stretch();
		static Graph* Pyramid();

		static std::vector<Graph*> Generate(int, int);
	};
}


