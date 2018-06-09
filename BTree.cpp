#include "BTree.h"
#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

BTree::~BTree(){
    deleteAll(root);
};

void BTree::deleteAll(Node *subTreeRoot){
    if (subTreeRoot == nullptr)
        return;
    
    deleteAll(subTreeRoot->left);
    deleteAll(subTreeRoot->right);
    delete subTreeRoot;
}

BTree::BTree(map<char, int> &table){
    priority_queue<Node*, vector<Node*>, compare> queue;
    for (auto const& entry : table)
        queue.push(new Leaf(entry.first, entry.second, nullptr, nullptr));
    
    makeTree(queue);
}

void BTree::makeTree(priority_queue<Node*, vector<Node*>, compare> &queue){
    while (queue.size() > 1){
        Node* node1 = queue.top();
        queue.pop();
        Node* node2 = queue.top();
        queue.pop();
        
        queue.push(new Node(node1->data + node2->data, node1, node2));
    }
    
    root = decodingPointer = queue.top();
    queue.pop();
}

void BTree::prettyPrint() const {
	prettyPrint(0, root);
}

void BTree::prettyPrint(int counter, Node* subTreeRoot) const {
	if (subTreeRoot == nullptr)
		return;

	prettyPrint(counter + 1, subTreeRoot->right);

	for (int i = 0; i < counter; ++i)
		cout << "\t";
	cout << (subTreeRoot->data) << endl;
	if (isLeaf(subTreeRoot)){
		for (int i = 0; i < counter; ++i)
			cout << "\t";
		cout << static_cast<Leaf*>(subTreeRoot)->str << endl;
	}

	prettyPrint(counter + 1, subTreeRoot->left);
}

bool BTree::consumeSymbol(char symbol, char &character){
    if (symbol & 1) decodingPointer = decodingPointer->right;
    else            decodingPointer = decodingPointer->left;
    
    if (!isLeaf(decodingPointer))
        return false;
    else {
        character = static_cast<Leaf*>(decodingPointer)->str;
        decodingPointer = root;
        return true;
    }
}

string BTree::findCode(const char& symbol) const {
    if (isLeaf(root) && (static_cast<Leaf*>(root)->str == symbol))
        return "0";

	string result = "";
	if (findCode(symbol, result, root))
		return result;

	else return "";
}

bool BTree::findCode(const char& symbol, string &result, Node *subThreeRoot) const {
	if (subThreeRoot == nullptr)
		return false;

	if (isLeaf(subThreeRoot)){
        return static_cast<Leaf*>(subThreeRoot)->str == symbol;
	} else {
		if (findCode(symbol, result.append("0"), subThreeRoot->left))   return true;
		else                                                            result.pop_back();
		if (findCode(symbol, result.append("1"), subThreeRoot->right))  return true;
		else                                                            result.pop_back();
	}

	return false;
}

bool BTree::isLeaf(Node* subTreeRoot) const {
    return subTreeRoot != nullptr && subTreeRoot->left == nullptr && subTreeRoot->right == nullptr;
}
