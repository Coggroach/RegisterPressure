#include "Graphs.h"

namespace DataDependence 
{
	Graphs::Graphs() {	}

	Graphs::~Graphs(){	}

	Graph DataDependence::Graphs::Diamond()
	{
		auto g = Graph();

		g.AddVertex("s1", { "in" });
		g.AddVertex("s2", { "in2" });
		g.AddVertex("s3", { "s1" });
		g.AddVertex("s4", { "s1", "s2" });
		g.AddVertex("s5", { "s2" });
		g.AddVertex("s6", { "s3" });
		g.AddVertex("s7", { "s3" });
		g.AddVertex("s8", { "s4", "s5" });
		g.AddVertex("s9", { "s5" });
		g.AddVertex("s10", { "s6", "s7" });
		g.AddVertex("s11", { "s8" });
		g.AddVertex("s12", { "s10", "s11" });
		g.AddVertex("s13", { "s11", "s9" });
		g.AddVertex("s14", { "s12", "s13" });

		g.CreateMinimumChains();
		g.LinkVerticesToChains();
		g.Colours = 3;
		g.CreateSchedule();
		return g;
	}

	Graph DataDependence::Graphs::Droplets()
	{
		auto g = Graph();

		g.AddVertex("s1", { "in" });
		g.AddVertex("s2", { "in2" });
		g.AddVertex("s3", { "s1" });
		g.AddVertex("s4", { "s2" });
		g.AddVertex("s5", { "s2" });
		g.AddVertex("s6", { "s1", "s3" });
		g.AddVertex("s7", { "s2", "s5" });
		g.AddVertex("s8", { "s6" });
		g.AddVertex("s9", { "s4", "s7" });

		g.CreateMinimumChains();
		g.LinkVerticesToChains();
		g.Colours = 2;
		g.CreateSchedule();
		return g;
	}

	Graph Graphs::Mirror()
	{
		auto g = Graph();

		g.AddVertex("s1", { "in" });
		g.AddVertex("s2", { "s1" });
		g.AddVertex("s3", { "s1" });
		g.AddVertex("s4", { "s2" });
		g.AddVertex("s5", { "s3" });
		g.AddVertex("s6", { "s2", "s4" });
		g.AddVertex("s7", { "s3", "s5" });
		g.AddVertex("s8", { "s6", "s7" });

		g.CreateMinimumChains();
		g.LinkVerticesToChains();
		g.Colours = 3;
		g.CreateSchedule();
		return g;
	}

	Graph Graphs::Parallel()
	{
		auto g = Graph();

		g.AddVertex("s1", { "in" });
		g.AddVertex("s2", { "in2" });
		g.AddVertex("s3", { "s1" });
		g.AddVertex("s4", { "s1", "s4" });
		g.AddVertex("s5", { "s2" });
		g.AddVertex("s6", { "s5" });
		g.AddVertex("s7", { "s4" });
		g.AddVertex("s8", { "s5", "s6" });
		g.AddVertex("s9", { "s7", "s8" });

		g.CreateMinimumChains();
		g.LinkVerticesToChains();
		g.Colours = 3;
		g.CreateSchedule();
		return g;
	}

	Graph Graphs::Rombus()
	{
		auto g = Graph();

		g.AddVertex("s1", { "in" });
		g.AddVertex("s2", { "s1" });
		g.AddVertex("s3", { "s1" });
		g.AddVertex("s4", { "s3" });
		g.AddVertex("s5", { "s2" });
		g.AddVertex("s6", { "s3", "s4" });
		g.AddVertex("s7", { "s4" });
		g.AddVertex("s8", { "s5" });
		g.AddVertex("s9", { "s6", "s7" });
		g.AddVertex("s10", { "s8", "s10" });

		g.CreateMinimumChains();
		g.LinkVerticesToChains();
		g.Colours = 3;
		g.CreateSchedule();
		return g;
	}
}


