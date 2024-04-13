#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

class BinaryTree
{
public:
	class Node;

public:
	BinaryTree() = default;
	BinaryTree(const BinaryTree& other);
	~BinaryTree();

	bool isIdeal() const;
	bool isEmpty()const;

	Node* getRoot();
	Node* addNode(int key);

	int Height(Node* root) const;
	int Height() const;

	int NodeCount() const;
	int NodeCount(Node* root) const;

	void printHorizontal(int levelSpacing = 4) const;
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;

	BinaryTree clone() const;
	BinaryTree clone(Node* root) const;

	void clear();
	bool remove(int key);

	void clear(Node* root);
	Node* searchKey(int key);
	Node* searchKey(Node* root, int key) const;

	int Max(Node* root) const;
	int Max() const;

	int Min(Node* root) const;
	int Min() const;

	bool isBalanced(Node* root);
	bool isBalanced();

	std::vector<Node*> nodesVec();
	std::vector<Node*> nodesVec(Node* root);
	std::vector<int> keysVec();

	int level(int key);
	int level(Node* root, int key);

	Node* Parent(Node* root);
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