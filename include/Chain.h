#pragma once
#include <vector>

namespace DataDependence
{
	class Edge;

	class Chain
	{
	public:
		std::vector<Edge*> Edges;
		int Colour;

		Chain();
		~Chain();

		bool IsValidChain();
		bool ContainsVertex(Vertex*);
	};
}