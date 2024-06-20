#include"HuffmanTree.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
int main()
{
	class HuffmanTree tree;
	std::string orig = "original.txt";
	std::string encoded = "encoded.txt";
	std::string decoded = "decoded.txt";
	tree.build(orig);
	tree.printHorizontal();
	int cof = tree.encode(orig, encoded);
	std::cout << "cof:"<<cof;
	tree.decode(encoded, decoded);
}