#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <stdio.h>
using namespace std;

#ifndef BTREE_H_
#define BTREE_H_

struct Node {
	Node *left, *right;
	int data;

	Node(const int& d, Node *l, Node *r): left(l), right(r), data(d){}
	Node() :left(nullptr), right(nullptr){}
};

struct Leaf : public Node{
	char str;

	Leaf() : Node() {}
	Leaf(char _data, const int& d, Node* l, Node* r) : Node(d, l, r), str(_data) {}
};

struct compare{
	bool operator()(Node* l, Node* r){
		return (l->data > r->data);
	}
};

class BTree{
private:
	Node *root, *decodingPointer;
	void deleteAll(Node*);
	bool isLeaf(Node*) const;
	void makeTree(priority_queue<Node*, vector<Node*>, compare>&);
	bool findCode(const char&, string&, Node*) const;
	void prettyPrint(int counter, Node* subTreeRoot) const;
public:
	BTree(map<char, int>&);
	~BTree();
	string findCode(const char&) const;
	void prettyPrint() const ;
	bool consumeSymbol(char, char&);
};

#endif
