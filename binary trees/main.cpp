

#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include "BinaryTree.h"

int main() {
	BinaryTree tree;
	tree.addNode(55);
	tree.addNode(-2);
	tree.addNode(-412);
	tree.addNode(312);
	tree.addNode(77);
	tree.addNode(-5);
	tree.addNode(13);
	tree.addNode(2);
	tree.clear(-5);
	if (tree.searchKey(2)) 
	{
		tree.printHorizontal();
	}
	std::cout <<std::endl << "Hight:" << tree.Hight();
	std::cout << std::endl << "Count:" << tree.NodeCount();
	tree.clear();
}