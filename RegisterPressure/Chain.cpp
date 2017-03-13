#include "Chain.h"
#include "Edge.h"
#include "Vertex.h"
#include <algorithm>

namespace DataDependence
{
	Chain::Chain()
	{
		this->Edges = std::vector<Edge*>();
		this->Marked = false;
	}

	Chain::~Chain()
	{ 
		this->Edges.clear();
	}

	bool Chain::IsValidChain()
	{
		auto size = this->Edges.size() - 1;
		for (auto i = 0; i < size; i++)
		{
			if (this->Edges[i]->Child->Name != this->Edges[i + 1]->Parent->Name)
				return false;
		}
		return size > 0;
	}

	bool Chain::ContainsVertex(Vertex* v)
	{
		return std::any_of(this->Edges.begin(), this->Edges.end(), [v](Edge* e) { return e->Parent == v || e->Child == v; });
	}

	int Chain::GetChainLength()
	{
		auto total = 0;
		for (auto e : this->Edges)
			total += e->Distance;
		return total;
	}
}
