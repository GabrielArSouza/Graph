#include "algorithms/dijkstra.h"

void removeVertex (std::vector<Vertex> &freeSet, Vertex vertex)
{
	for (auto it = freeSet.begin(); it != freeSet.end(); ++it )
		if (it->getId() == vertex.getId()) freeSet.erase(it,it+1);
}

void updateReference (std::vector<Vertex> &freeSet, UGraph &graph)
{
	for (unsigned int i=0; i < freeSet.size(); i++)
		freeSet[i] = graph.getVertex(freeSet[i].getId());
}

void dijkstra (UGraph &graph)
{
	//inicializate free set
	auto freeSet = graph.getVertices();

	graph.getVertices()[0].setPathWeight(0);
	removeVertex(freeSet, graph.getVertices()[0]);

	// inicializate
	auto adjList = graph.getVertices()[0].getAdjList();
	for (unsigned int i=0; i < adjList.size(); i++)
	{
		graph.getVertex(adjList[i].getId()).setLabeledBy(graph.getVertices()[0].getId());
		graph.getVertex(adjList[i].getId()).setPathWeight(graph.getEdgeWeight(graph.getVertices()[0],adjList[i]));
	}

	while ( !(freeSet.empty() )
	{
		std::cout << "Entrou no while\n";
		// choose the minimum
		Vertex min = freeSet[0];
		for (unsigned int i=1; i < freeSet.size(); i++)
		{
			if ( freeSet[i].getPathWeight() < min.getPathWeight() )
				min = freeSet[i];
		}

		//mark min
		removeVertex(freeSet, min);
		auto vertexMin = graph.getVertex(min.getId());
		for (unsigned int i=0; i < vertexMin.getAdjList().size(); i++)
		{
			int pathWeight = vertexMin.getPathWeight() + graph.getEdgeWeight(vertexMin, vertexMin.getAdjList()[i]);
			if (vertexMin.getAdjList()[i].getPathWeight() > pathWeight)
			{
				vertexMin.getAdjList()[i].setLabeledBy(vertexMin.getId());
				vertexMin.getAdjList()[i].setPathWeight(pathWeight);
			}	
		}
	}

}