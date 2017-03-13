#pragma once
#include <string>
#include <vector>

namespace DataDependence
{
	class Chain;
	class Edge;
	class Vertex
	{
	public:
		std::string Name;
		std::vector<std::string> Operands;
		std::vector<Edge*> Incoming;
		std::vector<Edge*> Outgoing;
		std::vector<Chain*> Chains;
		int Delay;
		int Line;

		Vertex();
		Vertex(std::string);
		Vertex(std::string, std::vector<std::string>);
		Vertex(std::string, std::vector<std::string>, int);
		~Vertex();

		bool IsSourceNode();
		bool IsSinkNode();
		Edge* GetUnmarkedOutGoing();
	};
}