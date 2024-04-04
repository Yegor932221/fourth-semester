#include "BinaryTree.h"
#include <assert.h>
#include <stdlib.h>
#include <iostream>

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

bool BinaryTree::isBalanced() const
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
	if (m_root) {
		return addNode(m_root, key);
	}
	else {
		return m_root = new Node(key);
	}
}

BinaryTree::Node* BinaryTree::addNode(Node* root, int key)
{
	if (!root) {
		root = new Node(key);
	}
	else if (rand() % 2) {
		root->setLeft(addNode(root->getLeft(), key));
	}
	else {
		root->setRight(addNode(root->getRight(), key));
	}

	return root;
}

void BinaryTree::printHorizontal(int levelSpacing) const
{
	printHorizontal(m_root, 0, levelSpacing);
}

void BinaryTree::printHorizontal(Node* root, int marginLeft, int levelSpacing) const
{
	if (root == nullptr) {
		return;
	}

	printHorizontal(root->getRight(), marginLeft + levelSpacing, levelSpacing);
	std::cout << std::string(marginLeft, ' ') << root->getKey() << std::endl;
	printHorizontal(root->getLeft(), marginLeft + levelSpacing, levelSpacing);
}

BinaryTree BinaryTree::clone() const {
	return clone(m_root);
}

BinaryTree BinaryTree::clone(Node* root) const {
	BinaryTree clooone;
	if (root == nullptr) return clooone;
	clooone.m_root = _clone(root);
	return clooone;
}

BinaryTree::Node* BinaryTree::_clone() const {
	return _clone();
}

BinaryTree::Node* BinaryTree::_clone(Node* root) const {
	Node* cloneRoot = nullptr;
	if (root == nullptr) return cloneRoot;
	cloneRoot = new Node(root->getKey());
	cloneRoot->setLeft(clone(root->getLeft()).m_root);
	cloneRoot->setRight(clone(root->getRight()).m_root);
	return cloneRoot;
}


void BinaryTree::clear() {
	clear(m_root);
	m_root = nullptr;
}

void BinaryTree::clear(Node* root) {
	if (!root) return;
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
	if (root == nullptr) return 0;
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
	if (root == nullptr) return 0;
	hight_l = Hight(root->getLeft());
	hight_r = Hight(root->getRight());
	hight = 1 + std::max(hight_l, hight_r);
	return hight;
}

bool BinaryTree::clear(int key) {
	Node* cleared(searchKey(key));
	if (cleared == nullptr) 
		return false;
	else
	{
		clear(cleared);
		return true;
	}
}

BinaryTree::Node* BinaryTree::searchKey(int key)
{
	return searchKey(key, m_root);
}

BinaryTree::Node* BinaryTree::searchKey(int key, Node* root) 
{
	if (root == nullptr) return nullptr;
	if (root->getKey() == key)
	{
		return root;
	}
	Node* right(searchKey(key, root->getRight())), *left(searchKey(key, root->getLeft()));
	if (left != nullptr)
		return left;
	
	if (right != nullptr)
		return right;

	return nullptr;
}