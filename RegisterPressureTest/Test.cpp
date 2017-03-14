#include "Graph.h"
#include "Output.h"
#include "Graphs.h"

using namespace DataDependence;
using namespace Output;

int main()
{	
	WriteLine("Diamond", Graphs::Diamond());
	//WriteLine("Droplets", Graphs::Droplets());
	WriteLine("Mirror", Graphs::Mirror());
	WriteLine("Parallel", Graphs::Parallel());
	WriteLine("Rombus", Graphs::Rombus());

	ReadLine();
	return 0;
}