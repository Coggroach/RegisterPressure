#pragma once
#include <vector>

namespace DataDependence
{
	class Chain;
	class Vertex;
	class Scheduler
	{
	private:
		void init();

		Chain* findUnmarkedChain();
		std::vector<Vertex*> findAllSourceNodes();

		bool areParentsSchedulable(Vertex*);
		bool isVertexScheduled(Vertex*);
		bool isVertexSchedulable(Vertex*);
		bool isParentOverwritable(Vertex*);
		bool isLiveMarked(Vertex*);
		
		Vertex* findReleaseNode();

	public:
		std::vector<Vertex*>& Vertices;
		std::vector<Chain*>& Chains;
		std::vector<Vertex*> Start;
		std::vector<Vertex*> Release;
		std::vector<Vertex*> Schedule;
		std::vector<Vertex*> Live;
		int AvailableColours;
		int CurrentColours;

		Scheduler(std::vector<Vertex*>&, std::vector<Chain*>&);
		~Scheduler();

		void CreateSchedule();
	};
}