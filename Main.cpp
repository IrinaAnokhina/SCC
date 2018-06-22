#include<iostream>

#include"Graph.h"
#include"vld.h"

int main()
{
	int count{};
	Graph<char>g(++count);
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
	Graph<char>trG( ++count);
	trG = g;
	trG.printGraph();
	trG.printAdj();
	g.SCC(&trG);
	cout << "Amount of CSS is " << g.getSCC() << "\n";
}