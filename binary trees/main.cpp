#include <assert.h>
#include <stdlib.h>
#include <iostream>

class BinaryTree
{
public:
	class Node;

public:
	BinaryTree() = default;
	BinaryTree(const BinaryTree& other);
	~BinaryTree();

	bool isIdeal() const;
	bool isBalanced() const;

	Node* addNode(int key);

	void printHorizontal(int levelSpacing = 4) const;
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;

	BinaryTree clone() const;
	BinaryTree clone(Node* root) const;

	void clear();
	void clear(Node* root);
private:
	Node* addNode(Node* root, int key);
	Node* _clone() const;
	Node* _clone(Node* root) const;

private:
	Node* m_root = nullptr;
};

class BinaryTree::Node
{
public:
	Node(int key = 0, Node* left = nullptr, Node* right = nullptr);
	~Node() = default;

	int getKey() const;
	void setKey(int key);

	Node* getLeft();
	Node* getRight();
	void setLeft(Node* left);
	void setRight(Node* right);

private:
	int m_key = 0;
	Node* m_left = nullptr;
	Node* m_right = nullptr;
};

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
	this->m_root=other.clone().m_root;
}

BinaryTree::~BinaryTree()
{
	clear();
}

bool BinaryTree::isIdeal() const
{
	return false;
}

bool BinaryTree::isBalanced() const
{
	return false;
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

BinaryTree BinaryTree::clone(Node *root) const {
	BinaryTree clooone;
	if (root == nullptr) return clooone;
	clooone.m_root = _clone(root);
	return clooone;
}

BinaryTree::Node* BinaryTree::_clone() const {
	return _clone();
}

BinaryTree::Node* BinaryTree::_clone(Node* root) const {
	Node* cloneRoot=nullptr;
	if (root == nullptr) return cloneRoot;
	cloneRoot= new Node(root->getKey());
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