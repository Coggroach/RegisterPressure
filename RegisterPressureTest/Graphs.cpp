#include "Graphs.h"
#include "Graph.h"
#include "GraphFactory.h"

namespace DataDependence 
{
	Graph DataDependence::Graphs::Diamond()
	{
		return *(new GraphFactory(3)
			->Add("s1", { "in" })
			->Add("s2", { "in2" })
			->Add("s3", { "s1" })
			->Add("s4", { "s1", "s2" })
			->Add("s5", { "s2" })
			->Add("s6", { "s3" })
			->Add("s7", { "s3" })
			->Add("s8", { "s4", "s5" })
			->Add("s9", { "s5" })
			->Add("s10", { "s6", "s7" })
			->Add("s11", { "s8" })
			->Add("s12", { "s10", "s11" })
			->Add("s13", { "s11", "s9" })
			->Add("s14", { "s12", "s13" })->Build());
	}

	Graph DataDependence::Graphs::Droplets()
	{
		return *(new GraphFactory(2)
			->Add("s1", { "in" })
			->Add("s2", { "in2" })
			->Add("s3", { "s1" })
			->Add("s4", { "s2" })
			->Add("s5", { "s2" })
			->Add("s6", { "s1", "s3" })
			->Add("s7", { "s2", "s5" })
			->Add("s8", { "s6" })
			->Add("s9", { "s4", "s7" })->Build());
	}

	Graph Graphs::Mirror()
	{
		return *(new GraphFactory(3)
			->Add("s1", { "in" })
			->Add("s2", { "s1" })
			->Add("s3", { "s1" })
			->Add("s4", { "s2" })
			->Add("s5", { "s3" })
			->Add("s6", { "s2", "s4" })
			->Add("s7", { "s3", "s5" })
			->Add("s8", { "s6", "s7" })->Build());
	}

	Graph Graphs::Parallel()
	{
		return *(new GraphFactory(3)
			->Add("s1", { "in" })
			->Add("s2", { "in2" })
			->Add("s3", { "s1" })
			->Add("s4", { "s1", "s3" })
			->Add("s5", { "s2" })
			->Add("s6", { "s5" })
			->Add("s7", { "s4" })
			->Add("s8", { "s5", "s6" })
			->Add("s9", { "s7", "s8" })->Build());
	}

	Graph Graphs::Rombus()
	{
		return *(new GraphFactory(3)
			->Add("s1", { "in" })
			->Add("s2", { "s1" })
			->Add("s3", { "s1" })
			->Add("s4", { "s3" })
			->Add("s5", { "s2" })
			->Add("s6", { "s3", "s4" })
			->Add("s7", { "s4" })
			->Add("s8", { "s5" })
			->Add("s9", { "s6", "s7" })
			->Add("s10", { "s8", "s9" })->Build());
	}

	Graph Graphs::Stretch()
	{
		return *(new GraphFactory(3)
			->Add("s1", { "in" })
			->Add("s2", { "s1" })
			->Add("s3", { "s1" })
			->Add("s4", { "s2" })
			->Add("s5", { "s3" })
			->Add("s6", { "s5" })
			->Add("s7", { "s4" })
			->Add("s8", { "s5", "s6" })
			->Add("s9", { "s7" })
			->Add("s10", { "s8" })
			->Add("s11", { "s7", "s9" })
			->Add("s12", { "s8", "s10" })
			->Add("s13", { "s11", "s12" })->Build());
	}

	Graph Graphs::Pyramid()
	{
		return *(new GraphFactory(4)
			->Add("s1", { "in" })
			->Add("s2", { "in2" })
			->Add("s3", { "in3" })
			->Add("s4", { "in4" })
			->Add("s5", { "s1", "s2" })
			->Add("s6", { "s2", "s3" })
			->Add("s7", { "s3", "s4" })
			->Add("s8", { "s5", "s6" })
			->Add("s9", { "s6", "s7" })
			->Add("s10", { "s8", "s9" })->Build());
	}
}


