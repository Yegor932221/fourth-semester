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
	m_root = other._clone();
}

BinaryTree::~BinaryTree()
{
	clear();
}

BinaryTree::Node* BinaryTree::getRoot() const {
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
	BinaryTree clone;
	if (root == nullptr)
	{
		return clone;
	}
	clone.m_root = _clone(root);
	return clone;
}

BinaryTree::Node* BinaryTree::_clone() const 
{
	return _clone(m_root);
}

BinaryTree::Node* BinaryTree::_clone(Node* root) const 
{
	Node* cloneRoot = nullptr;
	if (root == nullptr)
	{
		return cloneRoot;
	}
	cloneRoot = new Node(root->getKey());
	cloneRoot->setLeft(_clone(root->getLeft()));
	cloneRoot->setRight(_clone(root->getRight()));
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

int BinaryTree::NodeCount(Node* root) const
{
	int count, count_l=0, count_r=0;
	if (root == nullptr) return 0;
	if (root->getLeft()!= nullptr) 
	{
		count_l = NodeCount(root->getLeft());
	}
	if (root->getRight()!= nullptr)
	{
		count_r = NodeCount(root->getRight());
	}
	count = 1 + count_l + count_r;
	return count;
}

int BinaryTree::NodeCount() const
{
	return NodeCount(m_root);
}

int BinaryTree::Height()const
{
	return Height(m_root);
}

int BinaryTree::Height(Node* root) const
{
	int height, height_l, height_r;
	if (root == nullptr) 
	{
		return 0;
	}
	height_l = Height(root->getLeft());
	height_r = Height(root->getRight());
	height = 1 + std::max(height_l, height_r);
	return height;
}

bool BinaryTree::remove(int key) 
{
	Node* node = searchKey(key);
	if (!node)
		return false;
	Node* replacementNode = nullptr;
	Node* nodeParent = Parent(node);
	Node* parentReplacementNode = nullptr;

	if (node->getLeft() && node->getRight())
	{
		replacementNode = nodesVec().back();
		parentReplacementNode = Parent(replacementNode);
		if (parentReplacementNode == node)
		{
			if (replacementNode == node->getLeft())
			{
				replacementNode->setRight(node->getLeft());
			}
			else
			{
				replacementNode->setLeft(node->getRight());
			}
		}
		else
		{
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
	if (node == m_root)
	{
		if (!node->getLeft() && !node->getRight())
		{
			delete m_root;
			m_root = nullptr;
			return true;
		}
		replacementNode = nodesVec().back();
		node->setKey(replacementNode->getKey());
		parentReplacementNode = Parent(replacementNode);
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

int BinaryTree::Max(Node* root)const 
{
	int max, left=INT_MIN, right=INT_MIN;
	if (root == nullptr) return INT_MIN;
	if (root->getLeft() != nullptr) 
	{
		left = Max(root->getLeft());
	}
	if (root->getRight() != nullptr)
	{
		right = Max(root->getRight());
	}
	max = std::max(left, right);
	max = std::max(max, root->getKey());
	return(max);
}

int BinaryTree::Max() const
{
	return Max(m_root);
}

int BinaryTree::Min(Node* root) const
{
	if (root == nullptr) return INT_MAX;
	int min, left = INT_MAX, right = INT_MAX;
	if (root->getLeft() != nullptr)
	{
		left = Min(root->getLeft());
	}
	if (root->getRight() != nullptr)
	{
		right = Min(root->getRight());
	}
	min = std::min(left, right);
	min = std::min(min, root->getKey());
	return(min);
}

int BinaryTree::Min() const
{
	return Min(m_root);
}

bool BinaryTree::isBalanced(Node* root)
{
	if (root == nullptr)
	{
		return true;
	}
	int right, left, difference;
	right = Height(root->getRight());
	left = Height(root->getLeft());
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

std::vector<BinaryTree::Node*> BinaryTree::nodesVec(Node* root) const
{
	if (root == nullptr)
	{
		std::vector<Node*> unprocessedNodes;
		return unprocessedNodes;
	}
	std::vector<Node*> Nodes;
	std::list<Node*> unprocessedNodes;
	unprocessedNodes.push_back(root);
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

std::vector<BinaryTree::Node*> BinaryTree::nodesVec() const
{
	return nodesVec(m_root);
}

std::vector<int> BinaryTree::keysVec() const
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

BinaryTree::Node* BinaryTree::Parent(Node* root) const
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

BinaryTree& BinaryTree::operator=(const BinaryTree& other)
{
	if (m_root == other.m_root)
		return *this;
	clear();
	m_root = other._clone(other.m_root);
	return*this;
}

std::vector<BinaryTree::Node*> BinaryTree::leafs() const
{
	std::list<Node*> nodeList;
	std::vector<Node*> leafs;
	nodeList.push_back(m_root);
	while (!nodeList.empty())
	{
		Node* node = nodeList.front();
		if (!(node->getLeft()) && !(node->getRight()))
		{
			leafs.push_back(node);
		}
		if (node->getLeft())
		{
			nodeList.push_back(node->getLeft());
		}
		if (node->getRight())
		{
			nodeList.push_back(node->getRight());
		}
		nodeList.pop_front();
	}
	return leafs;
}

std::vector<BinaryTree::Node*> BinaryTree::_leafs(Node* root) const
{
	std::list<Node*> nodeList;
	std::vector<Node*> leafs;
	nodeList.push_back(root);
	while (!nodeList.empty())
	{
		Node* node = nodeList.front();
		if (!(node->getLeft()) && !(node->getRight()))
		{
			leafs.push_back(node);
		}
		if (node->getLeft())
		{
			nodeList.push_back(node->getLeft());
		}
		if (node->getRight())
		{
			nodeList.push_back(node->getRight());
		}
		nodeList.pop_front();
	}
	return leafs;
}

void BinaryTree::printLeafs() const
{
	std::vector<Node*> vectorLeafs = leafs();
	for (Node* leafs : vectorLeafs)
	{
		std::cout << leafs->getKey() << " ";
	}
}

void BinaryTree::_treeToList(std::list<Node*>& nodeList) const 
{
	std::list<Node*> nodes;
	nodes.push_back(m_root);
	while (!nodes.empty())
	{
		Node* node = nodes.front();
		if (node->getLeft())
		{
			nodes.push_back(node->getLeft());
		}
		if (node->getRight())
		{
			nodes.push_back(node->getRight());
		}
		nodeList.push_back(node);
		nodes.pop_front();
	}
}