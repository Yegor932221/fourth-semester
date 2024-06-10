#include "HuffmanTree.h"
#include <fstream>
#include<iostream>
#include<string.h>
#include <vector>
#include <list>


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
	BoolVector simbols;
	for (int i = 0; i < 256; i++)
	{
		int k = 0;
		if (TAB[i] > 0)
		{
			const char s = static_cast<char>(i);
			simbols[k] = s;
			k++;
		}
	}
	HoarSort(TAB, 0, 255, simbols);
	for (int i = 0; i < simbols.size(); i++) 
	{
		std::string str(1, simbols[i]);
		Node now(str,herz[i],nullptr,nullptr);
		tree.push_back(&now);
	}
	for (;tree.size()>1;)
	{

		Node now(, herz[i], nullptr, nullptr);
	}
}
void HoarSort(int* arr, int l, int r, std::list <std::string>& simbols) {
	if (l >= r)
		return;
	int i = l;
	int j = r;
	int x = arr[(l + r) / 2];
	while (i <= j) {
		while (arr[i] < x) i++;
		while (arr[j] > x) j--;
		if (i <= j) {
			std::swap(arr[i], arr[j]);
			std::swap(simbols[i], simbols[j]);
			i++;
			j--;
		}
	}
	HoarSort(arr, l, j, simbols);
	HoarSort(arr, i, r, simbols);
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
