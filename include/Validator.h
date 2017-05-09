#pragma once

namespace DataDependence
{
	class Graph;
	class Validator
	{
	private:
		bool DoesIncomingEqualOutgoing(Graph*);
		bool DoesIncomingEqualVertex(Graph*);		
	public:
		Validator();
		~Validator();

		bool IsValid(Graph*);
	};
}