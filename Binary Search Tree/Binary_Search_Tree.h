#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include "C:\Users\Егор\fourth-semester\binary trees\BinaryTree.h"
class Binary_Search_Tree: public BinaryTree
{
public:
	Binary_Search_Tree() = default;
	Binary_Search_Tree(const Binary_Search_Tree& other);
	~Binary_Search_Tree();
	Node* addNode(int key);
	Node* addNode(Node* root,int key);
	void printHorizontal(int levelSpacing=4) const;
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;
private:
	Node* m_root = nullptr;
};

