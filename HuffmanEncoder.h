#include "BTree.h"


#ifndef HUFFMANENCODER_H_
#define HUFFMANENCODER_H_

class HuffmanEncoder{
	map<char, string> codeTable(map<char, int>&, BTree&) const;
	void encode(ifstream&, ofstream&) const;
public:
	HuffmanEncoder();
    void encode(const string&, const string&) const;
};

#endif
