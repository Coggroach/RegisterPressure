#include "Output.h"
#include "Scheduler.h"
#include <iostream>
#include <fstream>

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

void Output::WriteLine(std::string s, DataDependence::Graph *graph)
{
	WriteLine(s);
	WriteLine("==============");
	WriteLine("Vertices: " + std::to_string(graph->Vertices.size()));
	WriteLine("Edge: " + std::to_string(graph->Edges.size()));
	WriteLine("Chains: " + std::to_string(graph->Chains.size()));
	WriteLine("MaxColours: " + std::to_string(graph->Schedule->AvailableColours));
	WriteLine("CurrentColours: " + std::to_string(graph->Schedule->CurrentColours));
	WriteLine("PreviousColours: " + std::to_string(graph->Schedule->PreviousColours));
	WriteLine("Schedule: ", graph->Schedule->Schedule);
	WriteLine("==============");
}

void Output::WriteFile(std::string s, DataDependence::Graph* g)
{
	WriteFile(s, std::vector<DataDependence::Graph*>{ g });
}

void Output::WriteFile(std::string s, std::vector<DataDependence::Graph*> gs)
{
	std::ofstream o;
	o.open(s + ".csv");
	o << "Vertices,Edges,Chains,MaxColours,PreviousColours,Schedule" << std::endl;
	for (auto g : gs) 
	{
		o << std::to_string(g->Vertices.size()) << ",";
		o << std::to_string(g->Edges.size()) << ",";
		o << std::to_string(g->Chains.size()) << ",";
		o << std::to_string(g->Schedule->AvailableColours) << ",";
		o << std::to_string(g->Schedule->PreviousColours) << ",";
		for (auto i : g->Schedule->Schedule)
			if (i != nullptr)
				o << (i->Name + ":");
		o << std::endl;
	}
	o.close();
}

void Output::Write(std::string s, DataDependence::Graph* g)
{

}
