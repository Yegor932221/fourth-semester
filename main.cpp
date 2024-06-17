#include"HuffmanTree.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
int main()
{
	class HuffmanTree tree;
	std::string name = "pupupu.txt";
	const char* file= name.c_str();
	tree.build(file);
	tree.printHorizontal();
}