#include <stdlib.h>
#include <iostream>
#include <vector>
#include "BinaryTree.h"
#include"BinaryTreeTester.h"

int main() {

	srand(time(0));
	BinaryTreeTester tester(false, true);
	tester.test(5);
	BinaryTree tree;

	for(int i=0;i<100;i++) tree.addNode(i);
	tree.addNode(-2);
	tree.addNode(-412);
	tree.addNode(312);
	tree.addNode(-5);
	tree.addNode(-7);
	tree.addNode(789);
	/*tree.remove(50);*/
	if (tree.searchKey(2)) 
	{
		tree.printHorizontal();
	}
	std::cout <<std::endl << "Height:" << tree.Height();
	std::cout << std::endl << "Max:" << tree.Max();
	std::cout << std::endl << "Min:" << tree.Min();
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
	std::cout <<std::endl <<"Level 82:"<< tree.level(82)<<std::endl;

	int key;
	key = (tree.Parent(tree.searchKey(2)))->getKey();
	std::cout << std::endl << "Parent of 2:" <<key << std::endl;

	if(tree.remove(6)) tree.printHorizontal();
}