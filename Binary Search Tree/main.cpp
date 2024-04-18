#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Binary_Search_Tree.h"
#include "SearchTreeTester.h"
//#include"BinaryTreeTester.h"

int main() {

	SearchTreeTester tester(false, true);
	tester.test(100);
	Binary_Search_Tree tree;
	std::vector<int> keys;
	for (int i = 0; i < 5; i++)
	{
		tree.addNode(i * 10);
	}
	tree.addNode(-9);
	tree.addNode(-6);
	tree.addNode(-55);
	tree.addNode(-66);
	tree.addNode(-3);
	tree.addNode(-12);
	tree.addNode(-15);
	tree.addNode(-4);
	tree.addNode(33);
	tree.addNode(31);
	tree.addNode(22);
	tree.printHorizontal();
	std::cout << "Max: " << tree.max()<<std::endl;
	std::cout << "Min: " << tree.min()<<std::endl;
	std::cout << "Level 333: " << tree.level(tree.searchKey(333)) << std::endl;
	std::cout << "Parent of 20: " << tree.Parent(tree.searchKey(20))->getKey() << std::endl;
		

	/*keys = tree.keysVec();
	for (int i = 0; i < keys.size(); i++)
	{
		std::cout <<keys[i] <<" ";
	}*/
	
	tree.printHorizontal();


	std::cout << std::endl << "===========" << std::endl;
	std::cout << std::endl;
	tree.remove(-9);
	tree.printHorizontal();

	std::cout<<std::endl <<"===========" << std::endl;
	tree.remove(0);
	tree.printHorizontal();

	std::cout << std::endl << "===========" << std::endl;
	std::cout << std::endl;
	tree.remove(22);
	tree.printHorizontal();

	std::cout << std::endl << "===========" << std::endl;
	std::cout << std::endl;
	tree.remove(33);
	tree.printHorizontal();


	
	/*for (int i = 0; i < keys.size(); i++)
	{
		int key = keys[i];
		if (tree.searchKey(key))
		{
			std::cout << std::endl << "Have " << key << std::endl;
		}
		else std::cout << std::endl << "Haven't " << key << std::endl;
		key++;
		if (tree.searchKey(key))
		{
			std::cout << std::endl << "Have " << key << std::endl;
		}
		else std::cout << std::endl << "Haven't " << key << std::endl;
	}*/
	
	/*tree.printHorizontal();*/
}