#include "Binary_Search_Tree.h"
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>

Binary_Search_Tree::Binary_Search_Tree (const Binary_Search_Tree& other)
{
	m_root = other._clone();
}

Binary_Search_Tree::~Binary_Search_Tree() 
{
	clear();
}

Binary_Search_Tree::Node* Binary_Search_Tree::addNode(int key)
{
	if (m_root)
	{
		return addNode(m_root, key );
	}
	else
	{
		return m_root = new Node(key);
	}
}

Binary_Search_Tree::Node* Binary_Search_Tree::addNode(Node* root,int key)
{
	if (!root)
	{
		root = new Node(key);
	}
	else
	{
		if (root->getKey() < key)
		{
			root->setRight(addNode(root->getRight(),key));
		}
		else if (root->getKey() > key)
		{
			root->setLeft(addNode(root->getLeft(),key));
		}
		else if (root->getKey() == key) 
		{
			return root;
		}
	}
	return root;
}

void Binary_Search_Tree::printHorizontal(int levelSpacing	) const
{
	printHorizontal(m_root, 0, levelSpacing);
}

void Binary_Search_Tree::printHorizontal(Node* root, int marginLeft, int levelSpacing) const
{
	if (root == nullptr)
	{
		return;
	}
	printHorizontal(root->getRight(), marginLeft + levelSpacing, levelSpacing);
	std::cout << std::string(marginLeft, ' ') << root->getKey() << std::endl;
	printHorizontal(root->getLeft(), marginLeft + levelSpacing, levelSpacing);
}