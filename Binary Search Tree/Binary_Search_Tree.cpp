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

Binary_Search_Tree Binary_Search_Tree::clone() const
{
	return clone(m_root);
}

Binary_Search_Tree Binary_Search_Tree::clone(Node* root) const
{
	Binary_Search_Tree clone;
	if (root == nullptr)
	{
		return clone;
	}
	clone.m_root = _clone(root);
	return clone;
}

Binary_Search_Tree& Binary_Search_Tree::operator=(const Binary_Search_Tree& other)
{
	if (m_root == other.m_root)
		return *this;
	clear();
	m_root = other._clone(other.m_root);
	return*this;
}

int Binary_Search_Tree::max(Node* root)
{
	return address_max(root)->getKey();
}

Binary_Search_Tree::Node* Binary_Search_Tree::address_max(Node* root)
{
	if (root->getRight())
	{
	return address_max(root->getRight());
	}
	return root;
	
}

int Binary_Search_Tree::max()
{
	return address_max()->getKey();
}

Binary_Search_Tree::Node* Binary_Search_Tree::address_max()
{
	return address_max(m_root);
}


int Binary_Search_Tree::min(Node* root)
{
	return address_min(root)->getKey();
}

Binary_Search_Tree::Node* Binary_Search_Tree::address_min(Node* root)
{
	if (root->getLeft())
	{
		return address_min(root->getLeft());
	}
	return root;

}

int Binary_Search_Tree::min()
{
	return address_min()->getKey();
}

Binary_Search_Tree::Node* Binary_Search_Tree::address_min()
{
	return address_min(m_root);
}