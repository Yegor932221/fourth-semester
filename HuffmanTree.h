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
	void build(const char* text);
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;
	void printHorizontal(int levelSpacing=6) const;
	/*int encode(char text,char& coded);
	int encode(std::string text, char& coded);
	int encode(std::string text, std::string& coded);
	int encode(char text, std::string& coded);

	int decode(char decoded, char& coded);
	int decode(std::string decoded, char& coded);
	int decode(std::string decoded, std::string& coded);
	int decode(char decoded, std::string& coded);*/
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
	int Getfrequency() const;
	BoolVector getKey() const;
	void setKey(BoolVector key);
	
	Node* getLeft();
	Node* getRight();
	void setLeft(Node* left);
	void setRight(Node* right);
};

