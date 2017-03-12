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

	public:
		std::vector<Chain*>& Chains;
		std::vector<Vertex*> Start;
		std::vector<Vertex*> Release;
		std::vector<Vertex*> Schedule;

		Scheduler(std::vector<Chain*>&);
		~Scheduler();

		void CreateSchedule();
	};
}