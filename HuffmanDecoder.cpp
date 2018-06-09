#include "BTree.h"
#include "HuffmanDecoder.h"

void HuffmanDecoder::decode(ifstream &codeFile, ofstream &decodeFile){
	map<char, int>table;
	vector<string> readCharacters;
	string str = "";
	char characterToRead;
	char cToRead;

	string length="";
	for (int i = 0; i < 100; i++)
	{
		codeFile.get(cToRead);
	
		if (cToRead >= '0' && cToRead <= '9')
		{
			length = length + cToRead;
		}
		else break;
	}
	codeFile.clear();
	codeFile.seekg(length.size() + 1, ios::beg);
    
	int tableLength = stoi(length);

	bool chekFor = true;
	for (int i = 0; i < tableLength; i++)
	{
		codeFile.get(characterToRead);
		if (characterToRead == '#' && chekFor){
			readCharacters.push_back(str);
			str.clear();
			chekFor = false;
		}
		else{
			str = str + characterToRead;
			chekFor = true;
		}
	}

	for (int i = 0; i < readCharacters.size() - 1; i += 2){
		char key = readCharacters[i][0];
		int value = stoi(readCharacters[i + 1], 0, 10);
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
	for (int i = tableLength + length.size() + 1; i<fileLengthInBytes - 2; i++)
	{
		codeFile.get(charToRead);
		for (int i = 7; i >= 0; --i)
		{
			char bit = (((charToRead >> i) & 1) + 48);
			if (tree.consumeSymbol(bit, symbol))
			{
				decodeFile << symbol;
			}
		}

	}
	codeFile.get(charToRead);
	for (int i = 7; bitsToRead != 0; i--, bitsToRead--)
	{
		char bit = (((charToRead >> i) & 1) + 48);
		if (tree.consumeSymbol(bit, symbol))
		{
			decodeFile << symbol;
		}
	}


	decodeFile.close();
	codeFile.close();

}

HuffmanDecoder::HuffmanDecoder(){};
void HuffmanDecoder:: decode(){
	string codeFilePath;
	string decodeFilePath;

	cout << "Please enter a file of the code:\n";
	cin >> codeFilePath;
	cout << "Please enter a file for the decode:\n";
	cin >> decodeFilePath;

	ifstream codeFile(codeFilePath.c_str(), std::ifstream::in | std::ifstream::binary);
	ofstream decodeFile(decodeFilePath.c_str(), std::ofstream::out | std::ofstream::binary);

	decode(codeFile, decodeFile);
}


