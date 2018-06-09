#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <fstream>
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"
using namespace std;

int main(int argc, char** argv){
    if(argc != 4){
        cerr << "Not enough arguments." << endl;
        return 1;
    }

    if (strcmp("encode", argv[1]) == 0)
        (new HuffmanEncoder)->encode(argv[2], argv[3]);
    else if (strcmp("decode", argv[1]) == 0)
        (new HuffmanDecoder)->decode(argv[2], argv[3]);
    else {
        cerr << "Unrecognised command." << endl;
        return 1;
    }

    cout  << "Success!!!" << endl;
	return 0;
}
