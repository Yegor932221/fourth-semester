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
	tree.build(orig);
	/*tree.printHorizontal();*/
	int cof = tree.encode(orig, encoded);
}