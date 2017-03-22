#include "GraphFactory.h"
#include "Graph.h"

namespace DataDependence
{
	GraphFactory::GraphFactory(int c)
	{
		this->g = new Graph();
		this->g->Colours = c;
	}

	GraphFactory::~GraphFactory() { }

	GraphFactory * GraphFactory::Add(std::string name, std::vector<std::string> operands)
	{
		this->g->AddVertex(name, operands);
		return this;
	}

	Graph * GraphFactory::Build()
	{		
		this->g->CreateMinimumChains();
		this->g->LinkVerticesToChains();		
		this->g->CreateSchedule();
		return this->g;
	}
}