#include "HuffmanEncoder.h"

map<char, string> HuffmanEncoder::codeTable(map<char, int> table, BTree &tree){
	
	map<char, string> result;
	for (map<char, int>::iterator it = table.begin(); it != table.end(); it++)
	{
		result[it->first] = tree.findCode(it->first);
	}
	return result;
}
void HuffmanEncoder::encode(ifstream &file, ofstream &codeFile){
	map<char, int> table;
	char charToRead;

	while (file.get(charToRead))
		table[charToRead]++;

	BTree tree(table);

	string codeTab = "";

	map<char, string> tableOfCode = codeTable(table, tree);

	for (map<char, int>::iterator it = table.begin(); it != table.end(); it++)
	{
		string str = to_string(it->second);
		codeTab = codeTab + it->first + '#' + str + '#';
	}
     
	int tableLength = codeTab.length();
	codeFile << tableLength;
	codeFile << "?";
	codeFile << codeTab;

	file.clear();
	file.seekg(0, ios::beg);

	vector<bool> codeVector;
	char characterToRead;
    char codeSymbol = 0;
	while (file.get(characterToRead))
	{
		
		string temp = tableOfCode[characterToRead];
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp[i] == '0')
				codeVector.push_back(0);
			else codeVector.push_back(1);

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
		{
			codeVector.push_back(0);
		}
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
    HuffmanEncoder::HuffmanEncoder(){};

	void HuffmanEncoder::encode(){
		string filePath;
		string codeFilePath;

		cout << "Please enter a file path of the text:\n";
		cin >> filePath;
		cout << "Please enter a file for the code:\n";
		cin >> codeFilePath;

		ifstream file(filePath.c_str(), std::ifstream::in | std::ifstream::binary);
		ofstream codeFile(codeFilePath.c_str(), std::ofstream::out | std::ofstream::binary);

		encode(file, codeFile);
	}