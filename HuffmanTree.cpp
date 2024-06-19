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
			BoolVector symbols(256, 0);
			symbols[i]=1;
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

float  HuffmanTree::encode(const std::string& original, const std::string& encoded)
{
	float input=0,output=0;
	if (!m_root)
	{
		build(original);
	}
	std::ifstream originalFile(original, std::ios::binary);
	if (!originalFile.is_open())
	{
		std::cout << "File "<< original <<" not found!" << std::endl;
		return -1;
	}
	std::string sapport = "sapportFile_" + original;
	std::ofstream sapportFile(sapport, std::ios::binary);
	if (!sapportFile.is_open())
	{
		std::cerr << "Can't open file: " << encoded << std::endl;
		return -1;
	}

	int i = 0;
	BoolVector coded;
	const unsigned char* coded_el;
	while (!originalFile.eof())
	{
		unsigned char element;
		originalFile >> element;
		input++;
		BoolVector code(256, 0);
		Node* node = m_root;
		code[element]=1;
		while (node->getLeft() || node->getRight())
		{
			bool left = (((node->getLeft()->getKey()) &= code) == code);
			bool right = (((node->getRight()->getKey()) &= code) == code);
			if (left)
			{
				coded.Set0(0, i);
				i++;
				if (i == 8)
				{
					i = 0;
					output++;
					coded_el = coded.getCells();
					sapportFile << coded_el[0];
					coded.Set0All();
				}
				node = node->getLeft();
				continue;
			}
			if (right)
			{
				coded.Set1(0, i);
				i++;
				if (i == 8)
				{
					i = 0;
					output++;
					coded_el = coded.getCells();
					sapportFile << coded_el[0];
					coded.Set0All();
				}
				node = node->getRight();
				continue;
			}
				std::cerr << "there is no " << element << " in the tree"<< std::endl;
		}
	}
	output++;
	coded_el = coded.getCells();
	coded.Set0All();
	sapportFile << coded_el[0];
	originalFile.close();
	sapportFile.close();
	std::ofstream encodedFile(encoded, std::ios::binary);
	std::ifstream sapportEncodedFile(sapport, std::ios::binary);
	if (i==0)
	{
		encodedFile << 0;
	}
	else
	{
		encodedFile << (8 - i);
	}
	encodedFile << sapportEncodedFile.rdbuf();
	encodedFile.close();
	sapportEncodedFile.close();
	return (output /input)*100;
}

bool HuffmanTree::decode(const std::string& encoded, const std::string& decoded)
{
	std::ifstream encodedFile(encoded, std::ios::binary);
	std::ofstream dencodedFile(decoded, std::ios::binary);
	int insignificantCount;
	encodedFile >> insignificantCount;
	unsigned char element;
	encodedFile >> element;
	BoolVector search;
	search.addSymbol(element, 0);
	int i = 0;
	while (!encodedFile.eof())
	{
		Node* pointer= m_root;
		while (pointer->getLeft() && pointer->getRight())
		{
			if (i > 7)
			{
				encodedFile >> element;
				search.addSymbol(element, 0);
				i = 0;
			}
			if (encodedFile.eof()) 
			{
				while (i+insignificantCount<7)
				{
					if (search[i] == false)
					{
						pointer = pointer->getLeft();
						i++;
					}
					else if (search[i] == true)
					{
						pointer = pointer->getRight();
						i++;
					}
				}
				break;
			}
			if (search[i] == 1)
			{
				pointer = pointer->getRight();
				i++;
			}
			else if (search[i] == 0)
			{
				pointer = pointer->getLeft();
				i++;
			}
		}
		for (int j = 0; j < 256; j++) {
			if (pointer->getKey()[j] == 1)
			{
				dencodedFile << static_cast<unsigned char>(j);
				break;
			}
		}
	}
	return true;
}