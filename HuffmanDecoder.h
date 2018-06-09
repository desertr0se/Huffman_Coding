#include "BTree.h"

#ifndef HUFFMANDECODER_H_
#define HUFFMANDECODER_H_

class HuffmanDecoder{
	void decode(ifstream&, ifstream&, ofstream&) const;
	void decode(ifstream&, ofstream&) const;
public:
	HuffmanDecoder();
    void decode(const string&, const string&) const;
};

#endif
