#include "Scheduler.h"
#include "Chain.h"
#include "Vertex.h"
#include "Edge.h"
#include <algorithm>

namespace DataDependence
{
	void Scheduler::init()
	{
		this->initStartAndRelease();
		this->sortStartAndRelease();
		//this->AvailableColours = (this->Start.size() == this->Release.size()) ? this->Start.size() : 2 * this->Start.size() - this->Release.size() - 1;
		this->CurrentColours = 0;
		this->Live = std::vector<Vertex*>(this->AvailableColours, nullptr);
		this->scheduleIndex = 0;
	}

	void Scheduler::initStartAndRelease()
	{
		for (auto c : this->Chains)
		{
			auto u = c->Edges[0]->Parent;
			if (std::find(this->Start.begin(), this->Start.end(), u) == this->Start.end())
				this->Start.push_back(u);

			auto v = c->Edges[c->Edges.size() - 1]->Child;
			if (std::find(this->Release.begin(), this->Release.end(), v) == this->Release.end())
				this->Release.push_back(v);
		}
	}

	void Scheduler::sortStartAndRelease()
	{
		std::sort(this->Start.begin(), this->Start.end(), 
			[](Vertex* v1, Vertex* v2) { return v1->Line < v2->Line; });
		std::sort(this->Release.begin(), this->Release.end(), 
			[](Vertex* v1, Vertex* v2) { return v1->Line < v2->Line; });
	}

	Scheduler::Scheduler(std::vector<Vertex*>& v, std::vector<Chain*>& c, int cs) : Vertices(v), Chains(c)
	{
		this->Start = std::vector<Vertex*>();
		this->Release = std::vector<Vertex*>();
		this->Schedule = std::vector<Vertex*>(v.size(), nullptr);
		this->AvailableColours = cs;
		this->init();		
	}

	Scheduler::~Scheduler()
	{ 
		
	}

	void Scheduler::CreateSchedule()
	{		
		auto sourceNodes = this->findAllSourceNodes();
		if (sourceNodes.empty())
			return;
		auto root = sourceNodes[0];

		//Pick Starting Point root
		this->Schedule[this->scheduleIndex++] = root;
		root->RegisterName = "r0";
		this->Live[0] = root;
		this->CurrentColours++;

		Vertex* releaseNode, *iterate, *lastIterate;
		while((releaseNode = this->findReleaseNode()) != nullptr)
		{
			iterate = lastIterate = nullptr;
			do
			{
				lastIterate = iterate;
				iterate = iterateSchedule(releaseNode);				
			} while (iterate != releaseNode && iterate != nullptr && iterate != lastIterate);
			
			this->Release.erase(std::remove(this->Release.begin(), this->Release.end(), releaseNode), this->Release.end());
		}				
	}

	void Scheduler::VerifySchedule()
	{
		if (std::any_of(this->Schedule.begin(), this->Schedule.end(), [](Vertex* v) { return v == nullptr; }))
		{
			for (auto v : this->Vertices)
			{
				if (!this->isVertexScheduled(v))
					this->Schedule[this->scheduleIndex++] = v;
			}
		}
	}

	Chain* Scheduler::findUnmarkedChain()
	{
		for (auto c : this->Chains)
			if (!c->Marked)
				return c;
		return nullptr;
	}

	Chain* Scheduler::findBestChain(Vertex* v)
	{
		for (auto c : v->Chains)
		{
			auto curr = c->GetCurrentEdge();
			if (curr == nullptr)
				continue;
			if(this->isIncomingScheduled(curr->Child))
				return c;
		}
		for (auto e : v->Incoming)
		{
			if (this->isIncomingAllNull(e->Parent) && !this->isVertexScheduled(e->Parent))
			{
				for (auto c : v->Chains)
				{
					if (c->ContainsVertex(v) && c->ContainsVertex(e->Parent))
						return c;
				}
			}			
		}
		for (auto e : v->Incoming)
		{
			if (e->Parent == nullptr)
				continue;
			if (!this->isVertexScheduled(e->Parent))
				return this->findBestChain(e->Parent);						
		}
		return nullptr;
	}

	int Scheduler::findOverwritable(Edge* o)
	{
		for (int i = 0; i < this->Live.size(); i++)
		{
			auto l = this->Live[i];
			if (l == nullptr)
				continue;
			if (std::all_of(l->Outgoing.begin(), l->Outgoing.end(), [o](Edge* pe) { return o == pe || pe->Marked; }))
				return i;
		}
		return -1;
	}

	int Scheduler::findNullLive()
	{
		for (int i = 0; i < this->Live.size(); i++)
		{
			auto l = this->Live[i];
			if (l == nullptr)
				return i;
			if (std::all_of(l->Outgoing.begin(), l->Outgoing.end(), [](Edge* pe) { return pe->Marked; }))
				return i;
		}
		return -1;
	}

	std::vector<Vertex*> Scheduler::findAllSourceNodes()
	{
		auto vs = std::vector<Vertex*>();
		for (auto v : this->Vertices)
			if (v->IsSourceNode() && !v->IsSinkNode())
				vs.push_back(v);
		return vs;
	}

	bool Scheduler::isIncomingSchedulable(Vertex* v)
	{
		auto size = v->Incoming.size();
		auto isSchedulable = std::vector<bool>(size, false);
		for (int i = 0; i < size; i++)
		{
			auto e = v->Incoming[i];
			if (e->Parent == nullptr)
				return false;

			//Are GrandParents Dead? OR Is Already in Schedule? OR Is Parent a Child of Schedule?
			if (isIncomingAllNull(e->Parent) || isVertexScheduled(e->Parent) || isChildOfSchedule(e->Parent))
				isSchedulable[i] = true;
		}
		return std::all_of(isSchedulable.begin(), isSchedulable.end(), [](bool b) { return b; });
	}

	bool Scheduler::isIncomingScheduled(Vertex* v)
	{
		auto size = v->Incoming.size();
		auto isSchedulable = std::vector<bool>(size, false);
		for (int i = 0; i < size; i++)
		{
			auto e = v->Incoming[i];
			if (e->Parent == nullptr)
				return false;

			if (isVertexScheduled(e->Parent))
				isSchedulable[i] = true;
		}
		return std::all_of(isSchedulable.begin(), isSchedulable.end(), [](bool b) { return b; });
	}

	bool Scheduler::isChildOfSchedule(Vertex* v)
	{
		for (auto s : this->Schedule)
		{
			if (s == nullptr)
				continue;

			for (auto e : s->Outgoing)
			{
				if (e->Marked)
					continue;
				if (e->Child == v)
					return true;
			}
		}
		return false;
	}

	bool Scheduler::isIncomingAllNull(Vertex* v)
	{
		return std::all_of(v->Incoming.begin(), v->Incoming.end(), [](Edge* e) { return e->Parent == nullptr; });
	}

	bool Scheduler::isVertexScheduled(Vertex* v)
	{
		return std::any_of(this->Schedule.begin(), this->Schedule.end(), [v](Vertex* s) { return s != nullptr && v == s; });
	}

	bool Scheduler::isVertexSchedulable(Vertex *)
	{
		return false;
	}

	bool Scheduler::isIncomingOverwritable(Vertex* v)
	{
		for (auto e : v->Incoming) 
		{
			auto p = e->Parent;		
			if (p == nullptr)
				continue;
			auto m = std::all_of(p->Outgoing.begin(), p->Outgoing.end(), [e](Edge* pe) { return pe == e || pe->Marked; });
			if (m)
				return true;
		}
		return false;
	}

	bool Scheduler::isIncomingSafe(Vertex* v)
	{
		auto outgoing = 0;
		auto edges = std::vector<Edge*>();
		for (auto e : v->Incoming)
		{
			auto p = e->Parent;
			for (auto pe : p->Incoming)
			{
				if (pe->Parent == nullptr)
				{
					outgoing++;
					continue;
				}
				for (auto ope : pe->Parent->Outgoing)
				{
					if (std::find(edges.begin(), edges.end(), ope) == edges.end())
					{
						edges.push_back(ope);
						if (!ope->Marked)
							outgoing++;
					}					
				}					
			}
		}
		return outgoing <= this->AvailableColours;
	}

	Vertex* Scheduler::iterateSchedule(Vertex* releaseNode)
	{
		auto chain = this->findBestChain(releaseNode);
		if (chain == nullptr)
			return nullptr;

		auto edge = chain->GetCurrentEdge();		
		auto node = this->getUnscheduledVertex(edge);
		auto overwrite = this->isIncomingOverwritable(node);

		auto f = (overwrite) ? this->findOverwritable(edge) : this->findNullLive();
		if (f != -1)
		{
			for (auto e : node->Incoming)
				e->Marked = true;
			this->Live[f] = node;
			this->Schedule[this->scheduleIndex++] = node;
			node->RegisterName = "r" + std::to_string(f);
			if (!overwrite)
				this->CurrentColours++;
			return node;
		}
		return nullptr;
	}

	Vertex* Scheduler::findReleaseNode()
	{
		if (this->Release.size() == 0)
			return nullptr;

		auto index = 0;
		Vertex* node;
		do
		{
			node = this->Release[index];
			auto A = this->isIncomingSchedulable(node);
			auto B = this->isIncomingOverwritable(node);
			auto C = B && this->isIncomingSafe(node);
			
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
		} while (this->Release.size() > 0 && index < this->Release.size());
		return nullptr;
	}

	Vertex* Scheduler::findFloatingParent(Vertex* v)
	{
		for (auto i : v->Incoming)
			for(auto pi : i->Parent->Incoming)
				if (pi->Parent == nullptr && !this->isVertexScheduled(pi->Child))
					return pi->Child;
		return nullptr;
	}

	Vertex* Scheduler::getUnscheduledVertex(Edge* e)
	{
		return this->isVertexScheduled(e->Parent) ? e->Child : e->Parent;
	}
}