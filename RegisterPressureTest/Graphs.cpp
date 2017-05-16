#include "Graphs.h"
#include "Graph.h"
#include "RandomGraph.h"
#include "GraphFactory.h"
#include "RandomGraphFactory.h"

namespace DataDependence 
{
	Graph* DataDependence::Graphs::Diamond()
	{
		auto gf = new GraphFactory();
		auto g = gf->
			Add("s1", { "in" })->
			Add("s2", { "in2" })->
			Add("s3", { "s1" })->
			Add("s4", { "s1", "s2" })->
			Add("s5", { "s2" })->
			Add("s6", { "s3" })->
			Add("s7", { "s3" })->
			Add("s8", { "s4", "s5" })->
			Add("s9", { "s5" })->
			Add("s10", { "s6", "s7" })->
			Add("s11", { "s8" })->
			Add("s12", { "s10", "s11" })->
			Add("s13", { "s11", "s9" })->
			Add("s14", { "s12", "s13" })->Build();
		return g;
	}

	Graph* DataDependence::Graphs::Droplets()
	{
		auto gf = new GraphFactory();
		auto g = gf->
			Add("s1", { "in" })->
			Add("s2", { "in2" })->
			Add("s3", { "s1" })->
			Add("s4", { "s2" })->
			Add("s5", { "s2" })->
			Add("s6", { "s1", "s3" })->
			Add("s7", { "s2", "s5" })->
			Add("s8", { "s6" })->
			Add("s9", { "s4", "s7" })->Build();
		return g;
	}

	Graph* Graphs::Mirror()
	{
		auto gf = new GraphFactory();
		auto g = gf->
			Add("s1", { "in" })->
			Add("s2", { "s1" })->
			Add("s3", { "s1" })->
			Add("s4", { "s2" })->
			Add("s5", { "s3" })->
			Add("s6", { "s2", "s4" })->
			Add("s7", { "s3", "s5" })->
			Add("s8", { "s6", "s7" })->Build();
		return g;
	}

	Graph* Graphs::Parallel()
	{
		auto gf = new GraphFactory();
		auto g = gf->
			Add("s1", { "in" })->
			Add("s2", { "in2" })->
			Add("s3", { "s1" })->
			Add("s4", { "s1", "s3" })->
			Add("s5", { "s2" })->
			Add("s6", { "s5" })->
			Add("s7", { "s4" })->
			Add("s8", { "s5", "s6" })->
			Add("s9", { "s7", "s8" })->Build();
		return g;
	}

	Graph* Graphs::Rombus()
	{
		auto gf = new GraphFactory();
		auto g = gf->
			Add("s1", { "in" })->
			Add("s2", { "s1" })->
			Add("s3", { "s1" })->
			Add("s4", { "s3" })->
			Add("s5", { "s2" })->
			Add("s6", { "s3", "s4" })->
			Add("s7", { "s4" })->
			Add("s8", { "s5" })->
			Add("s9", { "s6", "s7" })->
			Add("s10", { "s8", "s9" })->Build();
		return g;
	}

	Graph* Graphs::Stretch()
	{
		auto gf = new GraphFactory();
		auto g = gf->
			Add("s1", { "in" })->
			Add("s2", { "s1" })->
			Add("s3", { "s1" })->
			Add("s4", { "s2" })->
			Add("s5", { "s3" })->
			Add("s6", { "s5" })->
			Add("s7", { "s4" })->
			Add("s8", { "s5", "s6" })->
			Add("s9", { "s7" })->
			Add("s10", { "s8" })->
			Add("s11", { "s7", "s9" })->
			Add("s12", { "s8", "s10" })->
			Add("s13", { "s11", "s12" })->Build();
		return g;
	}

	Graph* Graphs::Pyramid()
	{
		auto gf = new GraphFactory();
		auto g = gf->
			Add("s1", { "in" })->
			Add("s2", { "in2" })->
			Add("s3", { "in3" })->
			Add("s4", { "in4" })->
			Add("s5", { "s1", "s2" })->
			Add("s6", { "s2", "s3" })->
			Add("s7", { "s3", "s4" })->
			Add("s8", { "s5", "s6" })->
			Add("s9", { "s6", "s7" })->
			Add("s10", { "s8", "s9" })->Build();
		return g;
	}

	std::vector<Graph*> Graphs::Generate(int c, int s)
	{
		auto gf = new RandomGraphFactory();
		auto gs = std::vector<Graph*>();

		for(auto i = 0; i < c; i++)
			gs.push_back(gf->Build(s));

		return gs;
	}
}


