#pragma once
#include<list>
#include<iostream>
using std::ostream;

enum spectr { WHITE, GRAY, BLACK };

template<typename T>class Graph;

template<typename T>
class GraphNode
{
	friend class Graph<T>;

public:
	GraphNode(T val);
		
	~GraphNode();
	std::list<GraphNode<T>*> adjacency;
	void addToList(GraphNode<T>*);

private:
	GraphNode<T> *parent;
	T key;
	spectr color;
	int discovery;
	int finish;
	T getKey() { return key; }
};

template<typename T>
GraphNode<T>::GraphNode(T val)
	:parent(nullptr), key(val), color(WHITE), discovery(0), finish(0)
{
}

template<typename T>
GraphNode<T>::~GraphNode()
{}

template<typename T>
void GraphNode<T>::addToList(GraphNode<T> *node)
{
	adjacency.push_back(node);
}

