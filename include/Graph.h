#pragma once
#include <vector>
#include <string>

namespace DataDependence
{
	class Vertex;
	class Edge;
	class Chain;
	class Scheduler;
	class Graph
	{
	public:
		std::vector<Vertex*> Vertices;
		std::vector<Edge*> Edges;
		std::vector<Chain*> Chains;
		Scheduler* Schedule;
		int LineIndex;

		Graph();
		~Graph();

		Vertex* FindVertex(std::string);
		Vertex* FindSourceNode();

		bool ContainsVertex(std::string);
		void AddVertex(std::string, std::vector<std::string>);		

		void CreateMinimumChains();
		void LinkVerticesToChains();
		void UnmarkEdges();
		void UnmarkChains();
		void CreateSchedule();
	};
}