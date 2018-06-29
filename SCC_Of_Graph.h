#pragma once
#include<iostream>
using std::ostream;
using std::cout;
#include<iterator>
#include<deque>
#include<vector>
#include"GraphNode.h"

template<typename T>
class Graph
{
public:
	Graph() { ++graphCount; }
	~Graph();

	void addNode(T);
	void printGraph() const;
	void printAdj() const;
	void createAdj();
	void DFS();
	void topologicalSort();
	void SCC();
	const int getSCC() { return sccCount; }
private:
	Graph(const Graph<T> &);
	const Graph<T> &operator=(const Graph<T> &);
	std::list<GraphNode<T>*>my_graph;
	std::deque<GraphNode<T>>sorting;
	std::vector<GraphNode<T>*>components;
	GraphNode<T>* search(T);
	//main algorithm is using a graph transpose
	void transponing(const Graph<T> &);
	void DFS_Visit(GraphNode<T> *);
	void DFS2(GraphNode<T> *, Graph<T>&);
	bool operator==(const Graph<T> &) const;
	bool operator!=(const Graph &right) const
	{
		return !(*this == right);
	}
	static int graphCount;
	int time = 0;
	int sccCount = 0;
};

template<typename T>
int Graph<T>::graphCount = 0;

template<typename T>
Graph<T>::Graph(const Graph<T> &right)
{
	if (!right.my_graph.empty())
		for (auto j : right.my_graph)
		{
			T val = j->getKey();
			addNode(val);
		}
	++graphCount;
}

template<typename T>
Graph<T>::~Graph()
{
	cout << "Destroying graph ¹ " << graphCount << "\n";
	if (!my_graph.empty())
	{
		auto j = my_graph.begin();
		while (j != my_graph.end())
		{
			auto temp = j;
			++j;
			delete *temp;
		}
	}
	--graphCount;
}

template<typename T>
bool Graph<T>::operator==(const Graph<T> &right)const
{
	if (my_graph.size() != right->my_graph.size())
		return false;
	for (auto j : my_graph, auto i : right->my_graph)
		if (j->getKey() != i->getKey())
			return false;
}

template<typename T>
const Graph<T>& Graph<T>::operator=(const Graph<T> &right)
{
	if (this != &right)
	{
		my_graph.clear();
		for (auto j : right.my_graph)
		{

			T val = j->getKey();
			this->addNode(val);
		}
	}
	return *this;
}

template<typename T>
void Graph<T>::addNode(T key)
{
	GraphNode<T> *newNode = new GraphNode<T>(key);
	my_graph.push_back(newNode);
}

template<typename T>
void Graph<T>::printGraph() const
{
	if (!(my_graph.empty()))
	{
		std::cout << std::endl << "Graph contains " << my_graph.size() << " elements:\n";

		for (auto j : my_graph)
			cout << j->getKey() << " ";
		std::cout << std::endl;
	}
}

template<typename T>
void Graph<T>::printAdj() const
{
	if (!(my_graph.empty()))
	{
		for (auto j : my_graph)
		{
			cout << j->getKey();
			for (auto i : j->adjacency)
				cout << " -> " << i->getKey();
			cout << std::endl;
		}

	}
}

template<typename T>
GraphNode<T>* Graph<T>::search(T val)
{
	if (!my_graph.empty())
	{
		for (auto j : my_graph)
		{
			if (j->getKey() == val)
				return j;
		}
	}
	return nullptr;
}

template<typename T>
void Graph<T>::createAdj()
{
	T val{};
	T end{};
	char end_ch = '#';
	int end_i = -1;
	if (std::is_same<char, T>::value)
		end = end_ch;
	else
		end = end_i;
	cout << "Please, enter a -1, when finish to enter an adjacency list"
		<< " of current vertex, if your graph witn integer"
		<< " data and '#' if your graph with character-data\n";
	if (!(my_graph.empty()))
	{
		for (auto j : my_graph)
		{
			val = 0;
			cout << "Enter adjacency vertexes for vertex " << j->getKey() << ":\n";
			while (val != end)
			{
				std::cin >> val;
				GraphNode<T>* found = search(val);
				if (found != nullptr)
					j->addToList(found);
			}
		}
	}
}

template<typename T>
void Graph<T>::DFS()
{
	for (auto j : my_graph)
		if (j->color == WHITE)
			DFS_Visit(j);

}

template<typename T>
void Graph<T>::DFS_Visit(GraphNode<T> *node)
{
	time++;
	node->discovery = time;
	node->color = GRAY;

	cout << node->getKey() << " ";
	for (auto j : node->adjacency)
		if (j->color == WHITE)
		{
			j->parent = node;
			DFS_Visit(j);
		}
	node->color = BLACK;
	time++;
	node->finish = time;
	sorting.push_front(*node);
}

template<typename T>
void Graph<T>::topologicalSort()
{
	DFS();
	cout << "\n";
	for (auto j : sorting)
		cout << j.getKey() << " ";
}

template<typename T>
void Graph<T>::transponing(const Graph<T> &g)
{
	for (auto j : g.my_graph)
	{
		auto node = search(j->getKey());
		if (!j->adjacency.empty())
			for (auto i : j->adjacency)
			{
				auto cur = search(i->getKey());
				if (cur != nullptr && node != nullptr)
					cur->adjacency.push_back(node);
			}
	}
}

template<typename T>
void Graph<T>::SCC()
{
	topologicalSort();
	for (auto j : my_graph)
		j->color = WHITE;
	Graph<T>trG;
	trG = *this;
	trG.transponing(*this);
	trG.printGraph();
	trG.printAdj();
	for (size_t i = 0; i < sorting.size(); ++i)
	{
		T v = sorting[i].getKey();
		GraphNode<T>* cur = trG.search(v);
		cout << "\n";
		if (cur != nullptr)
			if (cur->color == WHITE)
			{
				DFS2(cur, trG);
				for (auto i : trG.components)
					cout << i->getKey() << " ";
				cout << "\n";
				trG.components.clear();
				++sccCount;
			}
	}
}

template<typename T>
void Graph<T>::DFS2(GraphNode<T> *vert, Graph<T> &transp)
{
	vert->color = GRAY;
	transp.components.push_back(vert);
	for (auto j : vert->adjacency)
		if (j->color == WHITE)
		{
			j->parent = vert;
			DFS2(j, transp);
		}
}