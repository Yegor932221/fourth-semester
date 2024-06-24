#include"HuffmanTree.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <sstream>
int main()
{
	class HuffmanTree tree;
	std::string orig = "original.txt";
	std::string encoded = "encoded.txt";
	std::string decoded = "decoded.txt";
	std::string exportFileName = "export.txt";
	
	/*tree.import(exportFileName);*/
	int cof = tree.encode(orig, encoded);
	std::cout << "\ncof:"<<cof << "\n";
	tree.printHorizontal();
	tree.exportTree(exportFileName);
	
	tree.decode(encoded, decoded);
	std::ifstream files[3] = {
		std::ifstream(orig),
		std::ifstream(encoded),
		std::ifstream(decoded)
	};

	for (int i = 0; i < 3; ++i) {
		std::stringstream stream;
		stream << files[i].rdbuf();
		std::cout << stream.str() << std::endl;
		files[i].close();
	}

	return 0;
}