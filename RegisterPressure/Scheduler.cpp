#include "Scheduler.h"
#include "Chain.h"
#include "Vertex.h"
#include "Edge.h"
#include <algorithm>

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
		this->AvailableColours = (this->Start.size() == this->Release.size()) ? this->Start.size() : 2 * this->Start.size() - this->Release.size() - 1;
		this->CurrentColours = 0;
		this->Live = std::vector<Vertex*>(this->AvailableColours, nullptr);
	}

	Scheduler::Scheduler(std::vector<Vertex*>& v, std::vector<Chain*>& c) : Vertices(v), Chains(c)
	{
		this->Start = std::vector<Vertex*>();
		this->Release = std::vector<Vertex*>();
		this->Schedule = std::vector<Vertex*>(v.size(), nullptr);		
		this->init();		
	}

	Scheduler::~Scheduler()
	{ 
		this->Start.clear();
		this->Release.clear();
		this->Schedule.clear();
		this->Live.clear();
	}

	void Scheduler::CreateSchedule()
	{		
		auto sourceNodes = this->findAllSourceNodes();
		auto root = sourceNodes[0];

		//Pick Starting Point root
		this->Schedule[0] = root;
		this->CurrentColours++;

		auto releaseNode = this->findReleaseNode();			
			
		//auto chains = 
	}

	Chain* Scheduler::findUnmarkedChain()
	{
		for (auto c : this->Chains)
			if (!c->Marked)
				return c;
		return nullptr;
	}

	std::vector<Vertex*> Scheduler::findAllSourceNodes()
	{
		auto vs = std::vector<Vertex*>();
		for (auto v : this->Vertices)
			if (v->IsSourceNode() && !v->IsSinkNode())
				vs.push_back(v);
		return vs;
	}

	bool Scheduler::areParentsSchedulable(Vertex* v)
	{
		for (auto e : v->Incoming)
		{
			if (isVertexScheduled(e->Parent))
				continue;
		}		
		//Can Dependents 

		//Are Dependents of Scheduled Schedulable? 

		return false;
	}

	bool Scheduler::isVertexScheduled(Vertex* v)
	{
		return std::any_of(this->Schedule.begin(), this->Schedule.end(), [v](Vertex* s) { return s != nullptr && v == s; });
	}

	bool Scheduler::isVertexSchedulable(Vertex *)
	{
		return false;
	}

	bool Scheduler::isParentOverwritable(Vertex *)
	{
		return false;
	}

	bool Scheduler::isLiveMarked(Vertex *)
	{
		return false;
	}

	Vertex * Scheduler::findReleaseNode()
	{
		if (this->Release.size() == 0)
			return nullptr;

		auto index = 0;
		Vertex* node;
		do
		{
			node = this->Release[index];
			auto A = this->areParentsSchedulable(node);
			auto B = this->isParentOverwritable(node);
			auto C = B && this->isLiveMarked(node);
			
			if (A)
				if (B)
					return node;
				else
					index++;
			else
				if (C)
					return node;
				else
					index++;
		} while (this->Release.size() > 0 || index < this->Release.size());
	}
}