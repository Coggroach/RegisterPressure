#include "Graph.h"
#include "Chain.h"
#include "Edge.h"
#include "Vertex.h"
#include "Scheduler.h"
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
		//delete this->Schedule;
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

	void Graph::LinkVerticesToChains()
	{
		for (auto c : this->Chains)
		{
			for (auto e : c->Edges)
			{
				auto p = e->Parent;
				if(p != nullptr) p->Chains.push_back(c);
			}				
			c->Edges[c->Edges.size() - 1]->Child->Chains.push_back(c);
		}
	}

	void Graph::UnmarkEdges()
	{
		for (auto e : this->Edges)
			e->Marked = (e->Parent == nullptr);
	}

	void Graph::UnmarkChains()
	{
		for (auto c : this->Chains)
			c->Marked = false;
	}

	void Graph::CreateSchedule()
	{
		this->Schedule = new Scheduler(this->Vertices, this->Chains, this->Colours);
		this->UnmarkEdges();
		this->UnmarkChains();
		this->Schedule->CreateSchedule();
		this->Schedule->VerifySchedule();
	}
}