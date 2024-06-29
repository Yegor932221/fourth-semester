#include "HashTable.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>
#include <assert.h>
#include <iterator>

int FirstHashFunction::hash(const int key, const int m_tableSize) const 
{
	return ((key % m_tableSize + d+c) % m_tableSize);
}

int SecondHashFunction::hash(const int key, const int m_tableSize) const
{
	static double a = (1 - std::sqrt(5)) / 2;
	return  (static_cast<int>(std::abs(key % m_tableSize *a*m_tableSize)) % m_tableSize);
}

int ThirdHashFunction::hash(const int key, const int m_tableSize) const
{
	return ((key % m_tableSize +(1+ key % (m_tableSize-2))) % m_tableSize);
}




