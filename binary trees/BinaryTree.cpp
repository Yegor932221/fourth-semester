#include "BinaryTree.h"
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>

BinaryTree::Node::Node(int key, Node* left, Node* right)
	: m_key(key)
	, m_left(left)
	, m_right(right)
{}

int BinaryTree::Node::getKey() const
{
	return m_key;
}

void BinaryTree::Node::setKey(int key)
{
	m_key = key;
}

BinaryTree::Node* BinaryTree::Node::getLeft()
{
	return m_left;
}

BinaryTree::Node* BinaryTree::Node::getRight()
{
	return m_right;
}

void BinaryTree::Node::setLeft(Node* left)
{
	m_left = left;
}

void BinaryTree::Node::setRight(Node* right)
{
	m_right = right;
}

BinaryTree::BinaryTree(const BinaryTree& other)
{
	this->m_root = other.clone().m_root;
}

BinaryTree::~BinaryTree()
{
	clear();
}

BinaryTree::Node* BinaryTree::getRoot() {
	return m_root;
}

bool BinaryTree::isIdeal() const
{
	return false;
}


bool BinaryTree::isEmpty() const
{
	if (m_root == nullptr) return true;
	else return false;
}

BinaryTree::Node* BinaryTree::addNode(int key)
{
	if (m_root) 
	{
		return addNode(m_root, key);
	}
	else 
	{
		return m_root = new Node(key);
	}
}

BinaryTree::Node* BinaryTree::addNode(Node* root, int key)
{
	if (!root) 
	{
		root = new Node(key);
	}
	else
	{

		if (rand() % 2)
		{
			root->setLeft(addNode(root->getLeft(), key));
		}
		else
		{
			root->setRight(addNode(root->getRight(), key));
		}
	}
	return root;
}

void BinaryTree::printHorizontal(int levelSpacing) const
{
	printHorizontal(m_root, 0, levelSpacing);
}

void BinaryTree::printHorizontal(Node* root, int marginLeft, int levelSpacing) const
{
	if (root == nullptr) 
	{
		return;
	}
	printHorizontal(root->getRight(), marginLeft + levelSpacing, levelSpacing);
	std::cout << std::string(marginLeft, ' ') << root->getKey() << std::endl;
	printHorizontal(root->getLeft(), marginLeft + levelSpacing, levelSpacing);
}

BinaryTree BinaryTree::clone() const 
{
	return clone(m_root);
}

BinaryTree BinaryTree::clone(Node* root) const 
{
	BinaryTree clooone;
	if (root == nullptr)
	{
		return clooone;
	}
	clooone.m_root = _clone(root);
	return clooone;
}

BinaryTree::Node* BinaryTree::_clone() const 
{
	return _clone();
}

BinaryTree::Node* BinaryTree::_clone(Node* root) const 
{
	Node* cloneRoot = nullptr;
	if (root == nullptr)
	{
		return cloneRoot;
	}
	cloneRoot = new Node(root->getKey());
	cloneRoot->setLeft(clone(root->getLeft()).m_root);
	cloneRoot->setRight(clone(root->getRight()).m_root);
	return cloneRoot;
}


void BinaryTree::clear() 
{
	clear(m_root);
	m_root = nullptr;
}

void BinaryTree::clear(Node* root) 
{
	if (!root)
	{
		return;
	}
	clear(root->getLeft());
	clear(root->getRight());
	delete root;
}

int BinaryTree::NodeCount() const
{
	return NodeCount(m_root);
}

int BinaryTree::NodeCount(Node* root) const
{
	int count, count_l, count_r;
	if (root == nullptr)
	{
	return 0;
	}
	count_l = NodeCount(root->getLeft());
	count_r = NodeCount(root->getRight());
	count = 1 + count_l + count_r;
	return count;
}

int BinaryTree::Hight()const
{
	return Hight(m_root);
}

int BinaryTree::Hight(Node* root) const
{
	int hight, hight_l, hight_r;
	if (root == nullptr) 
	{
		return 0;
	}
	hight_l = Hight(root->getLeft());
	hight_r = Hight(root->getRight());
	hight = 1 + std::max(hight_l, hight_r);
	return hight;
}

bool BinaryTree::clear(int key) 
{
	Node* cleared(searchKey(key));
	if (cleared == nullptr)
	{
		return false;
	}
	if (cleared->getLeft() == nullptr)
	{
		if (cleared->getRight() == nullptr)
		{
			clear(cleared);
			return true;
		}
		
	}
}

BinaryTree::Node* BinaryTree::searchKey(int key)
{
	return searchKey(m_root, key);
}


BinaryTree::Node* BinaryTree::searchKey(Node* root, int key) const
{
	if (!root || root->getKey() == key) 
	{
		return root;
	}
	Node* subTreeSearchResult = searchKey(root->getLeft(), key);
	if (!subTreeSearchResult) 
	{
		subTreeSearchResult = searchKey(root->getRight(), key);
	}
	return subTreeSearchResult;
}

int BinaryTree::MaxEl(Node* root)const 
{
	int max, left=INT_MIN, right=INT_MIN;
	if (root->getLeft() != nullptr) 
	{
		left = MaxEl(root->getLeft());
	}
	if (root->getRight() != nullptr)
	{
		right = MaxEl(root->getRight());
	}
	max = std::max(left, right);
	max = std::max(max, root->getKey());
	return(max);
}

int BinaryTree::MaxEl() const
{
	return MaxEl(m_root);
}

int BinaryTree::MinEl(Node* root) const
{
	int min, left = INT_MAX, right = INT_MAX;
	if (root->getLeft() != nullptr)
	{
		left = MinEl(root->getLeft());
	}
	if (root->getRight() != nullptr)
	{
		right = MinEl(root->getRight());
	}
	min = std::min(left, right);
	min = std::min(min, root->getKey());
	return(min);
}

int BinaryTree::MinEl() const
{
	return MinEl(m_root);
}

bool BinaryTree::isBalanced(Node* root)
{
	if (root != nullptr)
	{
		return true;
	}
	int right, left, difference;
	right = Hight(root->getRight());
	left = Hight(root->getLeft());
	difference = (right - left);
	difference=abs(difference);
	if (difference > 1)
	{
		return false;
	}	

		if (!isBalanced(root->getLeft()))
		{
			return false;
		}
		if (!isBalanced(root->getRight()))
		{
			return false;
		}
	return true;
}

bool BinaryTree::isBalanced()
{
	return isBalanced(m_root);
}

std::vector<BinaryTree::Node*> BinaryTree::nodesVec(Node* root)
{
	//ToDo: выйти, если root == nullptr
	if (root == nullptr)
	{
		std::vector<Node*> unprocessedNodes(1, nullptr);
		return unprocessedNodes;
	}
	std::vector<Node*> Nodes;
	std::list<Node*> unprocessedNodes(1, root);
	while (!unprocessedNodes.empty()) 
	{
		Node* node = unprocessedNodes.front();
		Nodes.push_back(node);
		if (node->getLeft()) 
		{
			unprocessedNodes.push_back(node->getLeft());
		}
		if (node->getRight()) 
		{
			unprocessedNodes.push_back(node->getRight());
		}
		unprocessedNodes.pop_front();
	}
	return Nodes;
}

std::vector<BinaryTree::Node*> BinaryTree::nodesVec() 
{
	return nodesVec(m_root);
}

std::vector<int> BinaryTree::keysVec()
{
	std::vector<Node*> Nodes=nodesVec(m_root);
	std::vector<int> array;
	for (int i = 0; i < Nodes.size(); i++)
	{
		array.push_back(Nodes[i]->getKey());
	}
	int step = array.size(), m;
	step = (step * 5 - 1) / 11;
	for (; step > 0;) {
		for (int i = 0; i < step; i++)
		{
			for (int j = i + step; j < array.size(); j += step)
			{
				int key = array[j];
				int k = j - step;
				while (k >= 0 && array[k] > key)
				{
					array[k + step] = array[k];
					k -= step;
				}
				array[k + step] = key;
			}
		}
		if (step == 1)break;
		m = (step * 5 - 1) / 11;
		step = std::max(m, 1);
	}
	return array;
}


int BinaryTree::level(Node* root,int key) 
{
	if (root == nullptr) return -1;
	if (root->getKey() == key) 
	{
		return 1;
	}
	if(level(root->getLeft(),key)>0)
	{
		return (level(root->getLeft(), key) + 1);
	}
	if (level(root->getRight(), key) > 0)
	{
		return (level(root->getRight(), key) + 1);
	}
}

int BinaryTree::level(int key) 
{
	return level(m_root, key);
}