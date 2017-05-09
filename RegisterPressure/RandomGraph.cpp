#include "RandomGraph.h"
#include "Vertex.h"
#include "Edge.h"
#include <random>
#include <algorithm>

namespace DataDependence
{
	RandomGraph::RandomGraph(int w) : Graph()
	{
		this->MaxCount = w;		
	}

	RandomGraph::~RandomGraph()	{ }

	void RandomGraph::Generate()
	{
		auto count = std::rand() % (this->MaxCount) + 5;
		auto vertices = std::vector<Vertex*>();

		for (auto i = 0; i < count; i++)
			vertices.push_back(new Vertex("s" + std::to_string(i), i));

		for (auto i = 0; i < count; i++)
		{
			auto numOfOperands = std::rand() % 2;

			for (auto j = 0; j < numOfOperands; j++)
			{
				auto op = getOperand(vertices, i);
				if(!op.empty())
					vertices[i]->Operands.push_back(op);
			}				
		}

		for (auto i = 0; i < count; i++)
			this->AddVertex(vertices[i]->Name, vertices[i]->Operands);
	}

	void RandomGraph::Trim()
	{
		auto newVertices = std::vector<Vertex*>();
		for (auto v : this->Vertices)
		{
			if (v->Incoming.size() == 0 && v->Outgoing.size() == 0)
				continue;

			if (v->Incoming.size() > 0)
			if (v->Incoming[0]->Parent == nullptr && v->Outgoing.size() == 0)
				continue;

			newVertices.push_back(v);
		}
		this->Vertices = newVertices;
	}

	std::string RandomGraph::getOperand(const std::vector<Vertex*>& vertices, int index)
	{
		if (index == 0)
			return std::string();
		return vertices[std::rand() % index]->Name;
	}
}