#include<iostream>

#include"SCC_Of_Graph.h"
#include"vld.h"

int main()
{
	int count{};
	Graph<char>g;
	g.addNode('a');
	g.addNode('b');
	g.addNode('c');
	g.addNode('d');
	g.addNode('e');
	g.addNode('f');
	g.addNode('g');
	g.addNode('h');

	g.printGraph();
	g.createAdj();
	g.printAdj();
	g.SCC();
	cout << "Amount of CSS is " << g.getSCC() << "\n";

}