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

	//WriteFile("R_1000_30", Graphs::Generate(1000, 30));
	//WriteFile("R_10000_30", Graphs::Generate(10000, 30));	

	//WriteFile("R_1000_60", Graphs::Generate(1000, 60));
	//WriteFile("R_10000_60", Graphs::Generate(10000, 60));
	

	//WriteFile("R_1000_120", Graphs::Generate(1000, 120));
	//WriteFile("R_10000_120", Graphs::Generate(10000, 120));

	//WriteFile("R_1000_180", Graphs::Generate(1000, 180));
	//WriteFile("R_10000_180", Graphs::Generate(10000, 180));

	//WriteFile("R_1000_270", Graphs::Generate(1000, 270));

	//WriteFile("R_1000_360", Graphs::Generate(1000, 360));

	//WriteFile("R_1000_720", Graphs::Generate(1000, 720));

	//WriteFile("R_10000_30_4", Graphs::Generate(10000, 30));

	WriteFile("R_1000_1440", Graphs::Generate(1000, 1440));

	//ReadLine();
	return 0;
}