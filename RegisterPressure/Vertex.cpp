#include "Vertex.h"
#include "Chain.h"
#include "Edge.h"
#include <algorithm>
#include <iterator> 

namespace DataDependence
{
	Vertex::Vertex() { }

	Vertex::Vertex(std::string n) : Vertex(n, std::vector<std::string>(), 0) { }

	Vertex::Vertex(std::string n, std::vector<std::string> v) : Vertex(n, v, 0) { }

	Vertex::Vertex(std::string n, std::vector<std::string> v, int l)
	{
		this->Name = n;
		this->Operands = v;
		this->Delay = 1;
		this->Incoming = std::vector<Edge*>();
		this->Outgoing = std::vector<Edge*>();
		this->Chains = std::vector<Chain*>();		
		this->Line = l;
	}

	Vertex::~Vertex() 
	{

	}

	bool Vertex::IsSourceNode()
	{		
		return std::all_of(this->Incoming.begin(), this->Incoming.end(), [](Edge* e) { return e->Marked; });
	}
	bool Vertex::IsSinkNode()
	{
		return this->Outgoing.size() == 0 || std::all_of(this->Outgoing.begin(), this->Outgoing.end(), [](Edge* e) { return e->Marked; });
	}
	Edge* Vertex::GetUnmarkedOutGoing()
	{
		std::vector<Edge*> edges;
		std::copy_if(this->Outgoing.begin(), this->Outgoing.end(), std::back_inserter(edges), [](const Edge* c) { return !c->Marked; });
		if(edges.size() > 0)
			return *std::max_element(edges.begin(), edges.end(), [](Edge* e, Edge* f) { return e->Distance < f->Distance; });
		return nullptr;
	}
}