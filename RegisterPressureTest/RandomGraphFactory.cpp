#include "RandomGraphFactory.h"
#include "RandomGraph.h"
#include "Validator.h"

namespace DataDependence
{
	RandomGraphFactory::RandomGraphFactory()
	{
		this->validator = new Validator();
	}

	RandomGraphFactory::~RandomGraphFactory() {	}

	RandomGraph* RandomGraphFactory::Build(int i)
	{
		auto g = new RandomGraph(i);
		g->Generate();
		g->Trim();

		if (!this->validator->IsValid(g))
		{
			delete g;
			return Build(i);
		}
		g->CreateMinimumChains();
		g->LinkVerticesToChains();
		g->CreateSchedule();
		return g;
	}
}


