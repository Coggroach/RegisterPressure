#include "Output.h"
#include "Scheduler.h"
#include <iostream>

void Output::WriteLine(std::string s)
{
	std::cout << s << std::endl;
}

void Output::WriteLine(std::vector<std::string> s)
{
	for (auto i : s)
		std::cout << i << " ";
	std::cout << std::endl;
}

std::string Output::ReadLine()
{
	std::string s;
	std::cin >> s;
	return s;
}

void Output::WriteLine(std::string s, std::vector<DataDependence::Vertex*> v)
{
	for (auto i : v)
		if(i != nullptr)
			std::cout << i->Name << "(" << i->RegisterName << ") " << std::endl;
}

void Output::WriteLine(std::string s, DataDependence::Graph graph)
{
	WriteLine(s);
	WriteLine("==============");
	WriteLine("Vertices: " + std::to_string(graph.Vertices.size()));
	WriteLine("Edge: " + std::to_string(graph.Edges.size()));
	WriteLine("Chains: " + std::to_string(graph.Chains.size()));
	WriteLine("MaxLive: " + std::to_string(graph.Schedule->AvailableColours));
	WriteLine("Schedule: ", graph.Schedule->Schedule);
	WriteLine("==============");
}

