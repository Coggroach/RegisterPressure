#include "Edge.h"
#include "Chain.h"
#include "Vertex.h"

namespace DataDependence 
{
	Edge::Edge() : Edge(nullptr, nullptr, 0) { }

	Edge::Edge(Vertex* p, Vertex* c, int d)
	{
		this->Parent = p;
		this->Child = c;
		this->Distance = d;
		this->Marked = false;
	}

	Edge::~Edge()
	{
		
	}
}
