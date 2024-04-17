#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Binary_Search_Tree.h"
//#include"BinaryTreeTester.h"

int main() {
	Binary_Search_Tree tree;
	
	for (int i = 0; i < 5; i++)
	{
		tree.addNode(i * 10);
	}
	tree.addNode(-9);
	tree.addNode(-6);
	tree.addNode(-55);
	tree.addNode(-3);
	tree.addNode(33);
	tree.addNode(31);
	tree.addNode(22);
	tree.printHorizontal();
	std::cout << "Max: " << tree.max()<<std::endl;
	std::cout << "Min: " << tree.min()<<std::endl;
	/*tree.printHorizontal();*/
}