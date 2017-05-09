#pragma once
#include <string>
#include <vector>

namespace DataDependence
{
	class RandomGraph;
	class Validator;
	class RandomGraphFactory
	{
	private:
		Validator* validator;
	public:
		RandomGraphFactory();
		~RandomGraphFactory();
				
		RandomGraph* Build();
	};
}



