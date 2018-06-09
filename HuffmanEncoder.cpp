#include "HuffmanEncoder.h"

HuffmanEncoder::HuffmanEncoder(){};

void HuffmanEncoder::encode(const string& filePath, const string& codeFilePath) const {
    ifstream fileStream(filePath.c_str(), std::ifstream::in | std::ifstream::binary);
    ofstream codeFileStream(codeFilePath.c_str(), std::ofstream::out | std::ofstream::binary);
    
    encode(fileStream, codeFileStream);
}

void HuffmanEncoder::encode(ifstream &file, ofstream &codeFile) const {
	map<char, int> table;
    for (char charToRead; file.get(charToRead);)
		table[charToRead]++;

	BTree tree(table);

	string codeTab = "";

	map<char, string> tableOfCode = codeTable(table, tree);

    for (auto const& it : table){
		string str = to_string(it.second);
		codeTab = codeTab + it.first + '#' + str + '#';
	}

	codeFile << codeTab.length() << "?" << codeTab;

	file.clear();
	file.seekg(0, ios::beg);

	vector<bool> codeVector;
	char characterToRead;
    char codeSymbol = 0;
	while (file.get(characterToRead)){
		string temp = tableOfCode[characterToRead];
		for (int i = 0; i < temp.size(); i++){
			if (temp[i] == '0') codeVector.push_back(0);
			else                codeVector.push_back(1);
		}

        while (codeVector.size() >= 8){
			for (int i = 7; i >= 0; --i){
				codeSymbol = codeSymbol | ((codeVector[0]) << i);
				codeVector.erase(codeVector.begin());
			}
			codeFile << codeSymbol;
			codeSymbol = 0;
		}
	}

	char bitLength = codeVector.size();
	if (codeVector.size() > 0){
        while (codeVector.size() < 8)
			codeVector.push_back(0);

		char codeSymbol = 0;
		for (int i = 7; i >= 0; --i){
			codeSymbol = codeSymbol | ((codeVector[0]) << i);
			codeVector.erase(codeVector.begin());
		}
		codeFile << codeSymbol;
	}

	codeFile << bitLength;
	codeFile.close();
	file.close();

}

map<char, string> HuffmanEncoder::codeTable(map<char, int>& table, BTree& tree) const {
    map<char, string> result;
    for (auto const& entry : table)
        result[entry.first] = tree.findCode(entry.first);

    return result;
}
