#include "Output.h"
#include "Scheduler.h"
#include <iostream>
#include <fstream>
#include <algorithm>

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

std::string TrackSumToString(int i, long& total)
{
	total += i;
	return std::to_string(i);
}

void Output::WriteFile(std::string s, std::vector<DataDependence::Graph*> gs)
{
	std::ofstream o;
	o.open(s + ".csv");
	o << "Vertices,Edges,Chains,MaxColours,UsedColours,PreviousColours,Gain,Schedule" << std::endl;
	long vs, es, cs, mc, uc, pc, ga;
	vs = es = cs = mc = uc = pc = ga = 0;
	for (auto g : gs) 
	{
		o << TrackSumToString(g->Vertices.size(), vs) << ",";
		o << TrackSumToString(g->Edges.size(), es) << ",";
		o << TrackSumToString(g->Chains.size(), cs) << ",";
		o << TrackSumToString(g->Schedule->AvailableColours, mc) << ",";
		auto curr = std::min(g->Schedule->AvailableColours, g->Schedule->PreviousColours);
		o << TrackSumToString(curr, uc) << ",";
		o << TrackSumToString(g->Schedule->PreviousColours, pc) << ",";
		o << TrackSumToString(g->Schedule->PreviousColours - curr, ga) << ",";
		for (auto i : g->Schedule->Schedule)
			if (i != nullptr)
				o << (i->Name + ":");
		o << std::endl;
	}
	o << vs << ",";
	o << es << ",";
	o << cs << ",";
	o << mc << ",";
	o << uc << ",";
	o << pc << ",";
	o << ga << ",";
	o.close();
}

void Output::Write(std::string s, DataDependence::Graph* g)
{

}
