#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>

class BinaryTree
{
public:
	class Node;

public:
	BinaryTree() = default;
	BinaryTree(const BinaryTree& other);
	virtual ~BinaryTree();

	bool isIdeal() const;
	bool isEmpty()const;

	Node* getRoot() const;
	virtual Node* addNode(int key);

	int height(Node* root) const;
	int height() const;

	int nodeCount() const;


	void printHorizontal(int levelSpacing = 4) const;
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;

	BinaryTree clone() const;
	BinaryTree clone(Node* root) const;

	void clear();
	virtual bool remove(int key);

	void clear(Node* root);
	virtual Node* searchKey(int key);
	virtual Node* searchKey(Node* root, int key) const;

	virtual int max(Node* root) const;
	virtual int max() const;
	
	virtual int min(Node* root) const;
	virtual int min() const;

	bool isBalanced(Node* root);
	bool isBalanced();

	std::vector<Node*> nodesVec() const;
	std::vector<Node*> nodesVec(Node* root) const;
	virtual std::vector<int> keysVec() const;

	int level(int key);
	int level(Node* root, int key);

	virtual Node* parent(Node* root) const;
	BinaryTree& operator=(const BinaryTree& other);

	std::vector<Node*> leafs() const;
	std::vector<Node*> _leafs(Node* root) const;

	void printLeafs() const;

	void _treeToList(std::list<Node*>& nodeList) const;
	Node* _clone() const;
	Node* _clone(Node* root) const;
private:
	Node* addNode(Node* root, int key);
	
protected:
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