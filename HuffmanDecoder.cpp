#include "BTree.h"
#include "HuffmanDecoder.h"

HuffmanDecoder::HuffmanDecoder(){};

void HuffmanDecoder::decode(const string& codeFilePath, const string& decodeFilePath) const {
    ifstream fileStream(codeFilePath.c_str(), std::ifstream::in | std::ifstream::binary);
    ofstream codeFileStream(decodeFilePath.c_str(), std::ofstream::out | std::ofstream::binary);
    
    decode(fileStream, codeFileStream);
}

void HuffmanDecoder::decode(ifstream &codeFile, ofstream &decodeFile) const {
	map<char, int>table;
	vector<string> readedCharacters;
	string str = "";
	char characterToRead, cToRead;

	string length="";
	for (int i = 0; i < 100; i++){
		codeFile.get(cToRead);
	
		if (cToRead >= '0' && cToRead <= '9')   length += cToRead;
		else                                    break;
	}

	codeFile.clear();
	codeFile.seekg(length.size() + 1, ios::beg);
    
	int tableLength = stoi(length);

	bool chekFor = true;
	for (int i = 0; i < tableLength; i++){
		codeFile.get(characterToRead);
		if (characterToRead == '#' && chekFor){
			readedCharacters.push_back(str);
			str.clear();
			chekFor = false;
		} else {
			str = str + characterToRead;
			chekFor = true;
		}
	}

	for (int i = 0; i < readedCharacters.size() - 1; i += 2){
		char key = readedCharacters[i][0];
		int value = stoi(readedCharacters[i + 1], 0, 10);
		table[key] = value;
	}

	BTree tree(table);

	char charToRead;
	char symbol;
	codeFile.seekg(-1, codeFile.end);
	char bitsToRead;
	codeFile.get(bitsToRead);
	int fileLengthInBytes = codeFile.tellg();
	codeFile.clear();
	codeFile.seekg(tableLength + length.size() + 1, ios::beg);

    for (int i = tableLength + length.size() + 1; i<fileLengthInBytes - 2; i++){
		codeFile.get(charToRead);
		for (int i = 7; i >= 0; --i){
			char bit = ((charToRead >> i) & 1);
			if (tree.consumeSymbol(bit, symbol))
				decodeFile << symbol;
		}
	}
    
	codeFile.get(charToRead);
	for (int i = 7; bitsToRead != 0; i--, bitsToRead--){
		char bit = ((charToRead >> i) & 1);
		if (tree.consumeSymbol(bit, symbol))
			decodeFile << symbol;
	}


	decodeFile.close();
	codeFile.close();
}
