#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include "C:\Users\Егор\fourth-semester\binary trees\BinaryTree.h"
class Binary_Search_Tree: public BinaryTree
{
public:
	Binary_Search_Tree() = default;
	Binary_Search_Tree(const Binary_Search_Tree& other);
	~Binary_Search_Tree();
	Node* addNode(int key);
	Node* addNode(Node* root,int key);
	void printHorizontal(int levelSpacing=4) const;
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;
	Binary_Search_Tree clone() const;
	Binary_Search_Tree clone(Node* root) const;
	Binary_Search_Tree& operator=(const Binary_Search_Tree& other);
	int max(Node* root);
	Node* address_max(Node* root);
	int max();
	Node* address_max();

	int min(Node* root);
	Node* address_min(Node* root);
	int min();
	Node* address_min();

	void keysVec(Node* root, std::vector<int>& keys) const;
	std::vector<int> keysVec(Node* root) const;
	std::vector<int> keysVec() const;
	Node* searchKey(Node* root, int key) const;
	Node* searchKey(int key) const;

	bool remove(int key);
	Node* Parent(Node* root) const;

	int level(Node* node, Node* root) const;
	int level(Node* node) const;

private:
	Node* m_root = nullptr;
};

