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

int HuffmanTree::Node::getFrequency() const
{
	return m_frequency;
}

void HuffmanTree::Node::setFrequency(int frequency)
{
	m_frequency= frequency;
}

void HuffmanTree::build(const std::string& text)
{
	std::list<Node*> tree;
	std::ifstream file(text, std::ios::binary);
	if (!file.good())
	{
		std::cout << "File not found!" << std::endl;
		return;
	}
	int* TAB = new int[256];
	for (int i = 0; i < 256; i++) TAB[i] = 0;
	unsigned char el_now;
	while (file >> el_now)
	{
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
	for (std::list<Node*>::iterator it = tree.begin(); it != tree.end(); it++)
	{
		for (std::list<Node*>::iterator jt = tree.begin(); jt != tree.end(); jt++)
		{
			if ((*it)->getFrequency() < (*jt)->getFrequency())
			{
				std::swap(*it, *jt);
			}
		}
	}
	while(tree.size() !=1)
	{
		Node* left = tree.front();
		tree.pop_front();
		Node* right = tree.front();
		tree.pop_front();
		BoolVector key = right->getKey()|left->getKey();
		int frequency = right->getFrequency() + left->getFrequency();
		Node* node=new Node(key, frequency, left, right);
		tree.push_back(node);
		for (std::list<Node*>::iterator it = tree.begin(); it != tree.end(); it++)
		{
			for (std::list<Node*>::iterator jt = tree.begin(); jt != tree.end(); jt++)
			{
				if ((*it)->getFrequency() < (*jt)->getFrequency())
				{
					std::swap(*it, *jt);
				}
			}
		}
	}
	m_root = tree.front();
	delete []TAB;
}

void HuffmanTree::printHorizontal(Node* root, int marginLeft, int levelSpacing) const
{
	if (root == nullptr) {
		return;
	}

	printHorizontal(root->getRight(), marginLeft + levelSpacing, levelSpacing);
	for (int i = 0; i < 256; ++i)
	{
		if (root->getKey()[i] == true)
		{
			std::cout << std::string(marginLeft, ' ') << static_cast<char>(i) << std::endl;
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
