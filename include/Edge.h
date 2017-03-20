#pragma once

namespace DataDependence 
{
	class Vertex;
	class Edge
	{
	public:
		Vertex* Parent;
		Vertex* Child;
		int Distance;
		bool Marked;

		Edge();
		Edge(Vertex*, Vertex*, int);
		~Edge();
	};
} 