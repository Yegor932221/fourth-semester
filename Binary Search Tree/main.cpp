#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Binary_Search_Tree.h"
#include "SearchTreeTester.h"

int main() {

	/*SearchTreeTester tester(false, false);
	tester.setRemoveCheckEnabled(true);
	tester.test(1000);*/
	Binary_Search_Tree tree;
	std::cout << "Node count: " << tree.nodeCount() << std::endl;
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
	tree.addNode(233);
	tree.addNode(1);
	tree.addNode(52);

	tree.printHorizontal();
	
	keys = tree.keysVec();
	Binary_Search_Tree OptimalTree(Binary_Search_Tree::createOptimalTree(keys));
	std::cout<<std::endl << "OptimalTree: " << std::endl;
	OptimalTree.printHorizontal();


	std::vector<int> keys2 = {3,-33,87,5,44,789,9,0,-32,-5,98,777777, 3434, 56,3333333};
	Binary_Search_Tree OptimalTree2(Binary_Search_Tree::createOptimalTree(keys2));
	std::cout << std::endl << "OptimalTree2: " << std::endl;
	OptimalTree2.printHorizontal();
}