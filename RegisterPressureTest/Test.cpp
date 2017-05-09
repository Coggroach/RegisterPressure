#include "Graph.h"
#include "Output.h"
#include "Graphs.h"

using namespace DataDependence;
using namespace Output;

int main()
{	
	WriteLine("Diamond", Graphs::Diamond());	
	WriteLine("Mirror", Graphs::Mirror());
	WriteLine("Parallel", Graphs::Parallel());
	WriteLine("Rombus", Graphs::Rombus());	
	WriteLine("Stretch", Graphs::Stretch());
	WriteLine("Pyramid", Graphs::Pyramid());

	WriteFile("Randoms", Graphs::Generate(10000));

	ReadLine();
	return 0;
}