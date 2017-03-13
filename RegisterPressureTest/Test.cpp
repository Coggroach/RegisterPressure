#include "Graph.h"
#include "Scheduler.h"
#include "Output.h"

using namespace DataDependence;
using namespace Output;

int main()
{
	auto graph = new Graph();

	graph->AddVertex("s1", { "in" });
	graph->AddVertex("s2", { "in2" });
	graph->AddVertex("s3", { "s1" });
	graph->AddVertex("s4", { "s1", "s2" });
	graph->AddVertex("s5", { "s2" });
	graph->AddVertex("s6", { "s3" });
	graph->AddVertex("s7", { "s3" });
	graph->AddVertex("s8", { "s4", "s5" });
	graph->AddVertex("s9", { "s5" });
	graph->AddVertex("s10", { "s6", "s7" });
	graph->AddVertex("s11", { "s8" });
	graph->AddVertex("s12", { "s10", "s11" });
	graph->AddVertex("s13", { "s11", "s9" });
	graph->AddVertex("s14", { "s12", "s13" });

	graph->CreateMinimumChains();
	graph->LinkVerticesToChains();
	graph->CreateSchedule();

	WriteLine("Vertices: " + std::to_string(graph->Vertices.size()));
	WriteLine("Edge: " + std::to_string(graph->Edges.size()));
	WriteLine("Chains: " + std::to_string(graph->Chains.size()));
	WriteLine("Schedule: " + std::to_string(graph->Schedule->Schedule.size()));
	WriteLine("Live: " + std::to_string(graph->Schedule->AvailableColours));

	ReadLine();
	return 0;
}