#pragma once
#include <vector>
#include <string>

namespace DataDependence
{
	class Vertex;
	class Edge;
	class Chain;
	class Graph
	{
	public:
		std::vector<Vertex*> Vertices;
		std::vector<Edge*> Edges;
		std::vector<Chain*> Chains;
		int LineIndex;

		Graph();
		~Graph();

		Vertex* FindVertex(std::string);
		bool ContainsVertex(std::string);
		void AddVertex(std::string, std::vector<std::string>);
		Vertex* FindSourceNode();
		void CreateMinimumChains();
		void ColourChains(int);
		bool DoChainsOverlap(Chain*, Chain*);
	};
}