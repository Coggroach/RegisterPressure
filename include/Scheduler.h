#pragma once
#include <vector>

namespace DataDependence
{
	class Chain;
	class Vertex;
	class Edge;
	class Scheduler
	{
	private:
		void init();
		void initStartAndRelease();
		void sortStartAndRelease();

		bool isIncomingSchedulable(Vertex*);
		bool isIncomingScheduled(Vertex*);
		bool isChildOfSchedule(Vertex*);
		bool isIncomingAllNull(Vertex*);
		bool isVertexScheduled(Vertex*);
		bool isVertexSchedulable(Vertex*);
		bool isIncomingOverwritable(Vertex*);
		bool isIncomingSafe(Vertex*);
		
		
		Vertex* iterateSchedule(Vertex*);
		Vertex* findReleaseNode();
		Vertex* findFloatingParent(Vertex*);
		Vertex* getUnscheduledVertex(Edge*);
		Chain* findUnmarkedChain();
		Chain* findBestChain(Vertex*);
		int findOverwritable(Edge*);
		int findOverwritable();
		int findNullLive();
		std::vector<Vertex*> findAllSourceNodes();

		int scheduleIndex;

	public:
		std::vector<Vertex*>& Vertices;
		std::vector<Chain*>& Chains;
		std::vector<Vertex*> Start;
		std::vector<Vertex*> Release;
		std::vector<Vertex*> Schedule;
		std::vector<Vertex*> Live;
		int AvailableColours;
		int CurrentColours;
		int PreviousColours;

		Scheduler(std::vector<Vertex*>&, std::vector<Chain*>&, int);
		~Scheduler();
		
		void CalculatePreviousColours();
		void CreateSchedule();
		void VerifySchedule();
	};
}