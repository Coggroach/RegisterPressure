#include "Scheduler.h"
#include "Chain.h"
#include "Vertex.h"
#include "Edge.h"

namespace DataDependence
{
	void Scheduler::init()
	{
		for (auto c : this->Chains)
		{
			auto u = c->Edges[0]->Parent;
			if (std::find(this->Start.begin(), this->Start.end(), u) != this->Start.end())
				this->Start.push_back(u);

			auto v = c->Edges[c->Edges.size() - 1]->Child;
			if (std::find(this->Release.begin(), this->Release.end(), v) != this->Release.end())
				this->Release.push_back(v);
		}
	}

	Scheduler::Scheduler(std::vector<Chain*>& c) : Chains(c)
	{
		this->Start = std::vector<Vertex*>();
		this->Release = std::vector<Vertex*>();
		this->Schedule = std::vector<Vertex*>();
		this->init();
	}

	Scheduler::~Scheduler()
	{ 
		this->Start.clear();
		this->Release.clear();
		this->Schedule.clear();
	}

	void Scheduler::CreateSchedule()
	{

	}
}