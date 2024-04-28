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

BinaryTree::Node* Binary_Search_Tree::addNode(int key)
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

BinaryTree::Node* Binary_Search_Tree::addNode(Node* root,int key)
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
//
//void Binary_Search_Tree::printHorizontal(int levelSpacing	) const 
//{
//	printHorizontal(m_root, 0, levelSpacing);
//}
//
//void Binary_Search_Tree::printHorizontal(Node* root, int marginLeft, int levelSpacing) const 
//{
//	if (root == nullptr)
//	{
//		return;
//	}
//	printHorizontal(root->getRight(), marginLeft + levelSpacing, levelSpacing);
//	std::cout << std::string(marginLeft, ' ') << root->getKey() << std::endl;
//	printHorizontal(root->getLeft(), marginLeft + levelSpacing, levelSpacing);
//}
//
//Binary_Search_Tree Binary_Search_Tree::clone() const
//{
//	return clone(m_root);
//}
//
//Binary_Search_Tree Binary_Search_Tree::clone(Node* root) const
//{
//	Binary_Search_Tree clone;
//	if (root == nullptr)
//	{
//		return clone;
//	}
//	clone.m_root = _clone(root);
//	return clone;
//}

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

BinaryTree::Node* Binary_Search_Tree::address_max(Node* root)
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

BinaryTree::Node* Binary_Search_Tree::address_max()
{
	return address_max(m_root);
}


int Binary_Search_Tree::min(Node* root)
{
	return address_min(root)->getKey();
}

BinaryTree::Node* Binary_Search_Tree::address_min(Node* root)
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

BinaryTree::Node* Binary_Search_Tree::address_min()
{
	return address_min(m_root);
}

void Binary_Search_Tree::keysVec(Node* root, std::vector<int>& keys) const
{
	if (!root) {
		return;
	}
	keysVec(root->getLeft(), keys);
	keys.push_back(root->getKey());
	keysVec(root->getRight(), keys);
}

std::vector<int> Binary_Search_Tree::keysVec(Node* root) const
{
	std::vector<int> keys;
	keysVec(root, keys);
	return keys;
}

std::vector<int> Binary_Search_Tree::keysVec() const
{
	return keysVec(m_root);
}

BinaryTree::Node* Binary_Search_Tree::searchKey(Node* root,int key) const
{
	if (!root) {
		return nullptr;
	}
	else
	{
		if (root->getKey() == key)
		{
			return root;
		}
		else
		{
			if (root->getKey() > key)
			{
				return searchKey(root->getLeft(), key);
			}
			else
			{
				if (root->getKey() < key)
				{
					return searchKey(root->getRight(), key);
				}
			}
		}
	}
}

BinaryTree::Node* Binary_Search_Tree::searchKey(int key) const
{
	return searchKey(m_root, key);
}

bool Binary_Search_Tree::remove(int key)
{
	Node* node = searchKey(key);
	if (!node)
		return false;
	Node* replacementNode = nullptr;
	Node* nodeParent = parent(node);
	Node* parentReplacementNode = nullptr;
	if (node == m_root)
	{
		if (!node->getLeft() && !node->getRight())
		{
			delete m_root;
			m_root = nullptr;
			return true;
		}
		if (node->getLeft())
		{
			replacementNode = address_max(node->getLeft());
		}
		else replacementNode = address_min(node->getRight());
		node->setKey(replacementNode->getKey());
		parentReplacementNode = parent(replacementNode);
		if (replacementNode->getLeft())
		{
			parentReplacementNode->setRight(replacementNode->getLeft());
			replacementNode->setLeft(nullptr);
			delete replacementNode;
			return true;
		}
		if (replacementNode->getRight())
		{
			parentReplacementNode->setLeft(replacementNode->getRight());
			replacementNode->setRight(nullptr);
			delete replacementNode;
			return true;
		}
		if (parentReplacementNode->getRight() == replacementNode)
		{
			parentReplacementNode->setRight(nullptr);
		}
		if (parentReplacementNode->getLeft() == replacementNode)
		{
			parentReplacementNode->setLeft(nullptr);
		}
		delete replacementNode;
		return true;
	}
	if (node->getLeft() && node->getRight())
	{
		replacementNode = address_max(node->getLeft());
		parentReplacementNode = parent(replacementNode);
		if (parentReplacementNode == node)
		{
			if (replacementNode == node->getLeft())
			{
				node->setKey(replacementNode->getKey());
				node->setLeft(replacementNode->getLeft());
				replacementNode->setLeft(nullptr);
				delete replacementNode;
				return true;
			}
		}
		else
		{
			if (replacementNode->getLeft())
			{
				parentReplacementNode->setRight(replacementNode->getLeft());
				node->setKey(replacementNode->getKey());
				delete replacementNode;
				return true;
			}
			replacementNode->setLeft(node->getLeft());
			replacementNode->setRight(node->getRight());
		}
		if (parentReplacementNode->getLeft() == replacementNode)
		{
			parentReplacementNode->setLeft(nullptr);
		}
		if (parentReplacementNode->getRight() == replacementNode)
		{
			parentReplacementNode->setRight(nullptr);
		}
		if (nodeParent->getLeft() == node)
		{
			nodeParent->setLeft(replacementNode);
		}
		if (nodeParent->getRight() == node)
		{
			nodeParent->setRight(replacementNode);
		}
		delete node;
		return true;
	}

	if (!node->getLeft() && !node->getRight())
	{
		if (nodeParent->getRight() == node)
		{
			nodeParent->setRight(nullptr);
		}
		if (nodeParent->getLeft() == node)
		{
			nodeParent->setLeft(nullptr);
		}
		delete node;
		return true;
	}
	if (node->getLeft())
	{
		replacementNode = node->getLeft();
		if (nodeParent->getLeft() == node)
		{
			nodeParent->setLeft(replacementNode);
		}
		if (nodeParent->getRight() == node)
		{
			nodeParent->setRight(replacementNode);
		}
		delete node;
		return true;
	}
	if (node->getRight())
	{
		replacementNode = node->getRight();
		if (nodeParent->getLeft() == node)
		{
			nodeParent->setLeft(replacementNode);
		}
		if (nodeParent->getRight() == node)
		{
			nodeParent->setRight(replacementNode);
		}
		delete node;
		return true;
	}
}

BinaryTree::Node* Binary_Search_Tree::parent(Node* root) const
{
	std::list<Node*> unprocessedNodes;
	unprocessedNodes.push_back(m_root);
	while (!unprocessedNodes.empty())
	{
		Node* node = unprocessedNodes.front();
		if (node == nullptr) return nullptr;
		if (node->getLeft())
		{
			if (node->getLeft() == root)
			{
				return node;
			}
			unprocessedNodes.push_back(node->getLeft());
		}
		if (node->getRight())
		{
			if (node->getRight() == root)
			{
				return node;
			}
			unprocessedNodes.push_back(node->getRight());
		}
		unprocessedNodes.pop_front();
	}
	return nullptr;
}

int Binary_Search_Tree::level(Node* node, Node* root) const
{
	if (!node) {
		return -1;
	}
	else
	{
		if (root->getKey() == node->getKey())
		{
			return 1;
		}
		else
		{
			if (root->getKey() > node->getKey())
			{
				int Level = level(node, root->getLeft());
				if (Level != -1) return (Level + 1);
				else return -1;
			}
			else
			{
				if (root->getKey() < node->getKey())
				{
					int Level = level(node, root->getRight());
					if (Level != -1) return (Level + 1);
					else return -1;
				}
			}
		}
	}
}

int Binary_Search_Tree::level(Node* node) const
{
	return level(node, m_root);
}