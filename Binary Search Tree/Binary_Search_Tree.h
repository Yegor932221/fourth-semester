#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "C:\fourth-semester\binary trees\BinaryTree.h"
class Binary_Search_Tree : public BinaryTree
{
public:
	Binary_Search_Tree() = default;
	~Binary_Search_Tree() override;
	Node* addNode(int key) override;
	Node* addNode(Node* root,int key);
	Binary_Search_Tree& operator=(const Binary_Search_Tree& other);
	int max(Node* root);
	Node* address_max(Node* root);
	int max() ;
	Node* address_max();

	int min(Node* root);
	Node* address_min(Node* root);
	int min();
	Node* address_min();

	void keysVec(Node* root, std::vector<int>& keys) const;
	std::vector<int> keysVec(Node* root) const;
	std::vector<int> keysVec() const override;
	Node* searchKey(Node* root, int key) const;
	Node* searchKey(int key) const;

	bool remove(int key) override;
	bool remove(Node*& root, int key);
	bool remove(Node*& root, Node* node);
	bool remove(Node* node);
	Node* parent(Node* root) const override;

	int level(Node* node, Node* root) const;
	int level(Node* node) const;
	Node* parent(Node* root, Node* node) const;

	static Binary_Search_Tree createOptimalTree(std::vector<int> keys)
	{
		std::vector<int> vecKey = keys;
		std::sort(vecKey.begin(), vecKey.end());
		Binary_Search_Tree OTree;
		OTree.fillingOTree(0, keys.size()-1, vecKey);
		return OTree;
	};
	 void fillingOTree(int min, int max, std::vector<int> keys);
	/*int balance(Node* root);*/

};

