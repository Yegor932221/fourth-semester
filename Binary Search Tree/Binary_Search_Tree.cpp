#include "Binary_Search_Tree.h"
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

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
	if (root == nullptr) return INT_MIN;
	return address_max(root)->getKey();
}

BinaryTree::Node* Binary_Search_Tree::address_max(Node* root)
{
	if (root == nullptr) return root;
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
	if (root == nullptr) return INT_MAX;
	return address_min(root)->getKey();
}

BinaryTree::Node* Binary_Search_Tree::address_min(Node* root)
{
	if (root == nullptr) return root;
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


bool Binary_Search_Tree::remove(Node*& root,Node* node)
{
	if (!node)
		return false;
	
	if (node->getLeft() && node->getRight()) {
		Node* replacementNode = address_max(node->getLeft());
		node->setKey(replacementNode->getKey());
		return remove(node, replacementNode);
	}

	Node* child = node->getLeft();
	if (!child) {
		child = node->getRight();
	}

	Node* parent = this->parent(root, node);
	if (parent) {
		if (parent->getLeft() == node) {
			parent->setLeft(child);
		}
		else {
			parent->setRight(child);
		}
	}
	else {
		assert(node == root);
		root = child;
	}

	delete node;
	return true;
}

bool Binary_Search_Tree::remove(int key)
{
	return remove(m_root, key);
}
bool Binary_Search_Tree::remove(Node*& root, int key) 
{
	Node* node = searchKey(key);
	if (!node)
		return false;
	else
	{
		remove(root, node);
	}
}

//bool Binary_Search_Tree::remove( Node* node)
//{
//	if (!node->getLeft() || !node->getRight())
//	{
//		if (root->getLeft() == node) {
//			if (!node->getRight())
//			{
//				root->setLeft(node->getRight());
//				node->setRight(nullptr);
//			}
//			if (!node->getLeft())
//			{
//				root->setLeft(node->getLeft());
//				node->setLeft(nullptr);
//			}
//			delete node;
//			return true;
//		}
//		else {
//			if (!node->getRight())
//			{
//				root->setRight(node->getRight());
//				node->setRight(nullptr);
//			}
//			if (!node->getLeft())
//			{
//				root->setRight(node->getLeft());
//				node->setLeft(nullptr);
//			}
//			delete node;
//			return true;
//		}
//	}
//	if (!node->getLeft() && !node->getRight())
//	{
//		if (root->getLeft() == node)
//		{
//			root->setLeft(nullptr);
//		}
//		if (root->getRight() == node)
//		{
//			root->setRight(nullptr);
//		}
//		delete node;
//		return true;
//	}
//}

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

//Binary_Search_Tree createOptimalTree(std::vector<int> keys)
//{
//	std::vector<int> vecKey = keys;
//	std::sort(vecKey.begin(), vecKey.end());
//	Binary_Search_Tree OTree;
//	OTree.fillingOTree(0,keys.size(),vecKey);
//	return OTree;
//}

 void Binary_Search_Tree::fillingOTree(int min, int max, std::vector<int> keys)
{
	addNode(keys[(min + max) / 2]);
	if(((min + max)/2)-1-min>=0 && (min + max) / 2 >=1)
	{
		fillingOTree(min, ((min + max)/2) - 1, keys);
	}
	if (max- ((min + max) / 2) - 1>= 0)
	{
		fillingOTree(((min + max) / 2) + 1, max, keys);
	}
	return;
}

//int Binary_Search_Tree::balance(Node* root)
//{
//	int Balance,Balance_r=0,Balance_l=0;
//	if (root->getRight())
//	{
//		Balance_r =1+std::abs(balance(root->getRight()));
//	}
//	if (root->getLeft())
//	{
//		Balance_l =1+std::abs(balance(root->getLeft()));
//	}
//	Balance = Balance_r - Balance_l;
//	return(Balance);
//}

BinaryTree::Node* Binary_Search_Tree::parent(Node* child) const
{
	return BinaryTree::parent(child);
}

BinaryTree::Node* Binary_Search_Tree::parent(Node* root,Node* child) const
{
	std::list<Node*> unprocessedNodes;
	unprocessedNodes.push_back(root);
	while (!unprocessedNodes.empty())
	{
		Node* node = unprocessedNodes.front();
		if (node == nullptr) return nullptr;
		if (node->getLeft())
		{
			if (node->getLeft() == child)
			{
				return node;
			}
			unprocessedNodes.push_back(node->getLeft());
		}
		if (node->getRight())
		{
			if (node->getRight() == child)
			{
				return node;
			}
			unprocessedNodes.push_back(node->getRight());
		}
		unprocessedNodes.pop_front();
	}
	return nullptr;
}