#pragma once
#include "Graph.h"

namespace DataDependence
{
	class Graph;
	class Graphs
	{
	public:
		Graphs();
		~Graphs();

		static Graph Diamond();
		static Graph Droplets();
		static Graph Mirror();
		static Graph Parallel();
		static Graph Rombus();
	};
}


