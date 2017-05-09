#pragma once
#include <vector>
#include <string>
#include "Graph.h"

namespace DataDependence
{
	class RandomGraph : public Graph
	{
	public:

		int MaxCount;

		RandomGraph(int);
		~RandomGraph();

		void Generate();
		void Trim();
		std::string getOperand(const std::vector<Vertex*>&, int);
	};
}