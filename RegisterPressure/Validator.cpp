#include "Validator.h"
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"

namespace DataDependence
{
	Validator::Validator() { }

	Validator::~Validator()	{ }

	bool Validator::DoesIncomingEqualOutgoing(Graph* g)
	{
		for (auto v : g->Vertices)
		{
			for (auto e : v->Incoming)
			{
				for (auto e2 : v->Outgoing)
				{
					if (e->Parent->Name == e2->Child->Name)
						return true;
				}
			}
		}
		return false;
	}
	bool Validator::DoesIncomingEqualVertex(Graph* g)
	{
		return false;
	}

	bool Validator::IsValid(Graph* g)
	{
		return g->Vertices.size() > 0 && !DoesIncomingEqualVertex(g) && !DoesIncomingEqualOutgoing(g);
	}
}