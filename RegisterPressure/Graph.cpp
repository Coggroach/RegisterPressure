#include "Graph.h"
#include "Chain.h"
#include "Edge.h"
#include "Vertex.h"
#include <algorithm>

namespace DataDependence
{

	Graph::Graph()
	{
		this->Vertices = std::vector<Vertex*>();
		this->Edges = std::vector<Edge*>();
		this->Chains = std::vector<Chain*>();
		this->LineIndex = 0;
	}

	Graph::~Graph()
	{

	}

	Vertex * Graph::FindVertex(std::string n)
	{
		for (auto v : this->Vertices)
		{
			if (v->Name == n)
				return v;
		}
		return nullptr;
	}

	bool Graph::ContainsVertex(std::string n)
	{
		return FindVertex(n) != nullptr;
	}

	void Graph::AddVertex(std::string name, std::vector<std::string> operands)
	{
		auto childVertex = this->FindVertex(name);
		if (childVertex == nullptr)
		{
			childVertex = new Vertex(name, operands, this->LineIndex++);
			this->Vertices.push_back(childVertex);
		}

		for (auto o : operands)
		{
			auto parentVertex = this->FindVertex(o);
			auto difference = (parentVertex == nullptr) ? 0 : childVertex->Line - parentVertex->Line;
			auto edge = new Edge(parentVertex, childVertex, difference);
			if (parentVertex == nullptr)
				edge->Marked = true;
			this->Edges.push_back(edge);
			childVertex->Incoming.push_back(edge);
			if (parentVertex != nullptr)
				parentVertex->Outgoing.push_back(edge);
		}
	}

	Vertex * Graph::FindSourceNode()
	{
		for (auto v : this->Vertices)
		{
			if (v->IsSourceNode() && !v->IsSinkNode())
				return v;
		}
		return nullptr;
	}

	void Graph::CreateMinimumChains()
	{
		while (std::any_of(this->Edges.begin(), this->Edges.end(), [](Edge* e) { return !e->Marked; }))
		{
			auto u = this->FindSourceNode();
			if (u == nullptr)
				return;
			auto chain = new Chain();
			while (!u->IsSinkNode())
			{
				auto v = u->GetUnmarkedOutGoing();				
				chain->Edges.push_back(v);
				v->Marked = true;
				u = v->Child;
			}
			if (chain->Edges.size() > 0)
				this->Chains.push_back(chain);
			else
				delete chain;
		}
	}

	void Graph::ColourChains(int colours)
	{
		auto size = this->Chains.size();
		auto availableColours = (1L << colours + 1) - 1;
		for (auto i = 0; i < size - 1; i++)
		{
			for (auto j = i + 1; j < size; j++)
			{
				DoChainsOverlap(this->Chains[i], this->Chains[j]);
			}
		}
	}

	bool Graph::DoChainsOverlap(Chain* c0, Chain* c1)
	{
		for (auto v : c0->Edges)
		{
			if (c1->ContainsVertex(v->Parent))
				return true;
		}
		return c1->ContainsVertex(c0->Edges[c0->Edges.size() - 1]->Child);
	}
}