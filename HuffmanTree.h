#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "C:\ALGosy\hafman\hafman\BoolVector.h"

class HuffmanTree {
public:
	class Node;
	void build(const std::string& text);
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;
	void printHorizontal(int levelSpacing=6) const;
	float  encode(const std::string& original, const std::string& encoded);
	bool decode(const std::string& encoded, const std::string& decoded);
	void export(const std::string& text);
	std::vector<Node*> leafs() const;
	void import(const std::string& text);
	void clear(Node* root);
private:
	Node* m_root=nullptr;
};

class HuffmanTree::Node
{
public:
	Node(BoolVector symbols);
	~Node() = default;
	Node(BoolVector key, int frequency = 1, Node* left = nullptr, Node* right = nullptr);
private:
	BoolVector m_symbols;
	int m_frequency = 1;
	Node* m_leftChild = nullptr;
	Node* m_rightChild = nullptr;

public:
	int getFrequency() const;
	BoolVector getKey() const;
	void setKey(BoolVector key);
	
	Node* getLeft();
	Node* getRight();
	void setLeft(Node* left);
	void setRight(Node* right);
	void setFrequency(int frequency);
};

