#include "HuffmanTree.h"
#include <fstream>
#include<iostream>
#include<string.h>
#include <vector>
#include <list>
#include <iterator>


HuffmanTree::Node::Node(BoolVector key, int frequency, Node* left, Node* right)
	: m_symbols(key)
	, m_frequency(frequency)
	, m_leftChild(left)
	, m_rightChild(right)
{}

HuffmanTree::Node::Node(BoolVector symbols)
{
	setKey(symbols);
}

BoolVector HuffmanTree::Node::getKey() const
{
	return m_symbols;
}

void HuffmanTree::Node::setKey(BoolVector key)
{
	m_symbols = key;
}

HuffmanTree::Node* HuffmanTree::Node::getLeft()
{
	return m_leftChild;
}

HuffmanTree::Node* HuffmanTree::Node::getRight()
{
	return m_rightChild;
}

void HuffmanTree::Node::setLeft(Node* left)
{
	m_leftChild = left;
}

void HuffmanTree::Node::setRight(Node* right)
{
	m_rightChild = right;
}

void HuffmanTree::build(const char* text)
{
	FILE* mass;
	fopen_s(&mass, text, "r");
	if (mass == NULL)
	{
		perror("error opening file");
		getchar();
		exit(-1);
	}
	std::list<Node*> tree;
	std::ifstream file(text);
	int* TAB = new int[256];
	for (int i = 0; i < 256; i++) TAB[i] = 0;
	while (file.good())
	{
		char el_now;
		file >> el_now;
		TAB[el_now]++;
	}
	file.close();
	for (int i = 0; i < 256; i++)
	{
		if (TAB[i] > 0)
		{
			BoolVector symbols(256, false);
			symbols.Set1(0, i);
			tree.push_back(new Node(symbols, TAB[i], nullptr, nullptr));
		}
	}
	std::list<Node*>::iterator it = tree.begin();
	std::list<Node*>::iterator jt = tree.begin();
	for ( ;it != tree.end(); ++it)
	{
		for (; jt != tree.end(); ++jt)
		{
			if ((*it)->Getfrequency() > (*jt)->Getfrequency())
			{
				std::swap(*it, *jt);
			}
		}
	}
	while(tree.size()>1)
	{
		Node* left = tree.front();
		tree.pop_front();
		Node* right = tree.front();
		tree.pop_front();
		BoolVector key = right->getKey()&left->getKey();
		int frequency = right->Getfrequency() + left->Getfrequency();
		Node node(key, frequency, left, right);
		tree.push_back(&node);
	}
	m_root = tree.front();
}

int HuffmanTree::Node::Getfrequency() const
{
	return m_frequency;
}

void HuffmanTree::printHorizontal(Node* root, int marginLeft, int levelSpacing) const
{
	if (root == nullptr) {
		return;
	}

	printHorizontal(root->getRight(), marginLeft + levelSpacing, levelSpacing);
	std::cout << std::string(marginLeft-1, ' ');
	for (int i = 0; i < 256; ++i)
	{
		if (root->getKey()[i] == true)
		{
			std::cout << ' ' << static_cast<char>(i) << std::endl;
		}
	}
	printHorizontal(root->getLeft(), marginLeft + levelSpacing, levelSpacing);
}

void HuffmanTree::printHorizontal(int levelSpacing) const
{
	printHorizontal(m_root, 0, levelSpacing);
}

//int encode(char text, char& coded)
//{
//
//}
//
//int encode(std::string text, char& coded)
//{
//
//}
//
//int encode(std::string text, std::string& coded)
//{
//
//}
//
//int encode(char text, std::string& coded)
//{
//
//}
//
//int decode(char decoded, char& coded)
//{
//
//}
//
//int decode(std::string decoded, char& coded)
//{
//
//}
//
//int decode(std::string decoded, std::string& coded)
//{
//
//}
//
//int decode(char decoded, std::string& coded)
//{
//
//}
