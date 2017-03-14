#pragma once
#include <vector>

namespace DataDependence
{
	class Edge;
	class Vertex;
	class Chain
	{
	public:
		std::vector<Edge*> Edges;
		bool Marked;

		Chain();
		~Chain();

		bool IsValidChain();
		bool ContainsVertex(Vertex*);
		Vertex* GetCurrentVertex();
		Edge* GetCurrentEdge();
		int GetChainLength();
	};
}