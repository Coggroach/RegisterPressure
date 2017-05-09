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

	RandomGraph * RandomGraphFactory::Build()
	{
		auto g = new RandomGraph(30);
		g->Generate();
		g->Trim();

		if (!this->validator->IsValid(g))
		{
			delete g;
			return Build();
		}
		g->CreateMinimumChains();
		g->LinkVerticesToChains();
		g->CreateSchedule();
		return g;
	}
}


