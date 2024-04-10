

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
	//tree.clear(-5);
	if (tree.searchKey(2)) 
	{
		tree.printHorizontal();
	}
	std::cout <<std::endl << "Hight:" << tree.Hight();
	std::cout << std::endl << "Max:" << tree.MaxEl();
	std::cout << std::endl << "Min:" << tree.MinEl();
	std::cout << std::endl << "Count:" << tree.NodeCount();

	std::cout << std::endl << "IsBalanced:";
	if(tree.isBalanced())
	{
		std::cout << std::endl << "true"<< std::endl;
	}
	else
	{
		std::cout << std::endl << "false"<<std::endl;
	}

	std::vector<BinaryTree::Node*> nodes=tree.nodesVec();
	std::cout << std::endl << "Third:" <<nodes[2]->getKey() << std::endl;
	std::vector<int> keys = tree.keysVec();
	std::cout << "Sorted:";
	for (int i = 0; i < keys.size(); i++)
	{
		std::cout << keys[i] << " ";
	}
	std::cout <<std::endl <<"Level 82:"<< tree.level(82);

	tree.clear();
}