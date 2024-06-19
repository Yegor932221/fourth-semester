#include<assert.h>
#include<string>

#include "BoolVector.h"

BoolVector::BoolVector()
{
	m_length = 8;
	m_cellCount = 1;
	m_cells = new UC[m_cellCount];
	m_cells[0] = false;
}

BoolVector::BoolVector(UI length, const bool value)
{
	assert(length >= 0);
	m_length = length;
	m_cellCount = length / 8 + bool(length % 8);
	m_insignificantRankCount = (m_cellCount * m_cellSize) - m_length;
	m_cells = new UC[m_cellCount];
	uint8_t mask = 0;
	if (value)
	{
		mask = ~mask;
	}
	for (int i = 0; i < m_cellCount; i++)
	{
		m_cells[i] = mask;
	}
	m_cells[m_cellCount - 1] = m_cells[m_cellCount - 1] >> m_insignificantRankCount;
	m_cells[m_cellCount - 1] = m_cells[m_cellCount - 1] << m_insignificantRankCount;
}

BoolVector:: ~BoolVector()
{
	delete[] m_cells;
}

int BoolVector::Length()const
{
	return m_length;
}

BoolVector::BoolVector(const BoolVector& other)
	:m_length(other.m_length)
{
	m_cellCount = other.m_cellCount;
	m_cells = new UC[m_cellCount];
	m_insignificantRankCount = (m_cellCount * m_cellSize) - m_length;
	for (int i = 0; i < m_cellCount; i++)
	{
		m_cells[i] = other.m_cells[i];
	}
}

BoolVector::BoolVector(std::vector<bool>& vec)
{
	m_length = vec.size();
	m_cellCount = m_length / 8 + bool(m_length % 8);
	m_insignificantRankCount = (m_cellCount * m_cellSize) - m_length;
	m_cells = new UC[m_cellCount];
	for (int i = 0; i < vec.size(); ++i)
	{
		if (vec[i] == true)
			Set1(i / 8, i % 8);
		else
			Set0(i / 8, i % 8);
	}
	m_cells[m_cellCount - 1] = m_cells[m_cellCount - 1] >> m_insignificantRankCount;
	m_cells[m_cellCount - 1] = m_cells[m_cellCount - 1] << m_insignificantRankCount;
}

void BoolVector::Set1(const int cell, const int pos_cell)
{
	assert(cell >= 0 || cell < m_cellCount || pos_cell < m_cellSize);
	uint8_t mask = 1;
	mask = mask << (7 - pos_cell);
	m_cells[cell] = m_cells[cell] | mask;
}

void BoolVector::Set0(const int cell, const int pos_cell)
{
	assert(cell >= 0 || cell < m_cellCount || pos_cell < m_cellSize);
	uint8_t mask = 1;
	mask = mask << (7 - pos_cell);
	m_cells[cell] = m_cells[cell] & ~mask;

}

BoolVector::BoolVector(const char* str)
{
	m_length = strlen(str);
	m_cellCount = m_length / 8 + bool(m_length % 8);
	m_insignificantRankCount = (m_cellCount * m_cellSize) - m_length;
	m_cells = new UC[m_cellCount];
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == '1')
			Set1(i / 8, i % 8);
		else
			Set0(i / 8, i % 8);
	}
	m_cells[m_cellCount - 1] = m_cells[m_cellCount - 1] >> m_insignificantRankCount;
	m_cells[m_cellCount - 1] = m_cells[m_cellCount - 1] << m_insignificantRankCount;
}

void BoolVector::Swap(BoolVector& other)
{
	std::swap(m_cellCount, other.m_cellCount);
	std::swap(m_cells, other.m_cells);
	std::swap(m_length, other.m_length);
	std::swap(m_insignificantRankCount, other.m_insignificantRankCount);
}

BoolVector BoolVector::operator<<(const int count)const
{
	assert(count >= 0);
	BoolVector other(*this);
	if (count / m_cellSize == 0)
	{
		other.m_cells[0] <<= count;
		for (int i = 1; i < other.m_cellCount; i++)
		{
			UI mask = 0;		
			mask |= other.m_cells[i];
			mask >>= m_cellSize - count;
			other.m_cells[i - 1] |= mask;
			other.m_cells[i] <<= count;
		}
	}
	else
	{
		for (int i = 0; i < other.m_cellCount; i++)
		{
			if (i + count/ other.m_cellSize < other.m_cellCount)
			{	
				other.m_cells[i] = m_cells[i + (count / other.m_cellSize)];
				other.m_cells[i + (count / other.m_cellSize)] = 0;
			}
			else
			{
				other.m_cells[i] = 0;
			}
		}
		other.m_cells[0] <<= count % m_cellSize;
		for (int i = 1; i < other.m_cellCount; i++)
		{
			UI mask = 0;
			mask |= other.m_cells[i];
			mask >>= m_cellSize - count % m_cellSize;
			other.m_cells[i - 1] |= mask;
			other.m_cells[i] <<= count % m_cellSize;
		}
	}

	other.m_cells[m_cellCount - 1] >>= m_insignificantRankCount;
	other.m_cells[m_cellCount - 1] <<= m_insignificantRankCount;
	return other;
}

BoolVector BoolVector::operator>>(const int count)const
{
	assert(count >= 0);
	BoolVector other(*this);
	if (count / m_cellSize > 0)
	{
		for (int i = other.m_cellCount - 1; i >= 0; i--)
		{
			if (i - count / other.m_cellSize >= 0)
			{
				other.m_cells[i] = m_cells[i - (count / other.m_cellSize)];
				other.m_cells[i - (count / other.m_cellSize)] = 0;
			}
			else
				other.m_cells[i] = 0;
		}
	}
	other.m_cells[m_cellCount - 1] >>= count % m_cellSize;
	for (int i = other.m_cellCount - 2; i >= 0; i--)
	{
		UI mask = 0;
		mask |= other.m_cells[i];
		mask <<= m_cellSize - count % m_cellSize;
		other.m_cells[i + 1] |= mask;
		other.m_cells[i] >>= count % m_cellSize;
	}
	other.m_cells[m_cellCount - 1] = other.m_cells[m_cellCount - 1] >> m_insignificantRankCount;
	other.m_cells[m_cellCount - 1] = other.m_cells[m_cellCount - 1] << m_insignificantRankCount;
	return other;
}

void BoolVector::Invert()
{
	for (int i = 0; i < m_cellCount; i++) {
		m_cells[i] = ~m_cells[i];
	}
	m_cells[m_cellCount - 1] = m_cells[m_cellCount - 1] >> m_insignificantRankCount;
	m_cells[m_cellCount - 1] = m_cells[m_cellCount - 1] << m_insignificantRankCount;
}

void BoolVector::InvertElement(int index) {
	uint8_t mask = 1;
	mask = mask << (index % m_cellSize);
	m_cells[(index / m_cellSize) + 1] = m_cells[(index / m_cellSize) + 1] ^ mask;
}

void BoolVector::Set1InRange(int index, const int range)
{
	assert(index >= 0 || (index < m_cellCount && range < m_length));

	for (int i = 1; i <= range; i++, index++)
	{
		Set1(index / m_cellSize, index % m_cellSize);
	}
}

void BoolVector::Set0InRange(int index, const int range)
{
	assert(index >= 0 || (index < m_cellCount && range <= m_length));

	for (int i = 1; i <= range; i++, index++)
	{
		Set0(index / m_cellSize, index % m_cellSize);
	}
}

void BoolVector::Set1All()
{
	Set1InRange(0, m_length);
}

void BoolVector::Set0All()
{
	Set0InRange(0, m_length);
}

int BoolVector::Weight() const
{
	int count = 0;
	for (int i = 0; i < m_cellCount; i++)
	{
		for (int j = 0; j < m_cellSize; j++)
		{
			UI mask = 128;
			mask >>= j;
			mask &= m_cells[i];
			if (mask)
				count++;
		}
	}
	return count;
}

BoolVector::BoolRank::BoolRank(UC* cell, const int mask)
{
	m_cell = cell;
	m_mask = m_mask >> mask;
}

BoolVector::BoolRank BoolVector::operator[](const int index)
{
	assert(index>=0);
	return BoolRank(m_cells + index / m_cellSize, index % m_cellSize);
}

BoolVector BoolVector::operator&(const BoolVector& other)const
{
	assert(m_length == other.m_length);
	BoolVector tmp(*this);
	tmp &= other;
	return tmp;
}

BoolVector BoolVector::operator&=(const BoolVector& other) {
	assert(m_length == other.m_length);
	for (int i = 0; i < m_cellCount; i++)
	{
		m_cells[i] &= other.m_cells[i];
	}
	return *this;
}

BoolVector BoolVector::operator^(const BoolVector& other)const
{
	assert(m_length == other.m_length);
	BoolVector tmp(*this);
	tmp ^= other;
	return tmp;
}

BoolVector BoolVector::operator^=(const BoolVector& other) {
	assert(m_length == other.m_length);

	for (int i = 0; i < m_cellCount; i++)
	{
		m_cells[i] ^= other.m_cells[i];
	}
	return *this;
}

BoolVector BoolVector::operator|(const BoolVector& other)const
{
	assert(m_length == other.m_length);
	BoolVector tmp(*this);
	tmp |= other;
	return tmp;
}

BoolVector BoolVector::operator|=(const BoolVector& other) {
	assert(m_length == other.m_length);

	for (int i = 0; i < m_cellCount; i++)
	{
		m_cells[i] |= other.m_cells[i];
	}
	return *this;
}

BoolVector BoolVector::operator >>=(const int count)
{
	*this = *this >> count;
	return *this;
}

BoolVector BoolVector::operator <<=(const int count)
{
	*this = *this << count;
	return *this;
}

BoolVector BoolVector::operator ~()const
{
	BoolVector copy(*this);
	copy.Invert();
	return copy;
}

BoolVector& BoolVector::operator=(const BoolVector& other)
{
	if (m_cells == other.m_cells)
		return *this;

	if (m_cellCount != other.m_cellCount)
	{
		m_cellCount = other.m_cellCount;
		delete[] m_cells;
		m_cells = new UC[m_cellCount];
	}

	for (int i = 0; i < m_cellCount; i++)
	{
		m_cells[i] = other.m_cells[i];
	}

	m_length = other.m_length;
	m_insignificantRankCount = other.m_insignificantRankCount;
	return *this;
}
std::istream& operator >>(std::istream& stream, BoolVector& vector) {
	char* str = new char[vector.Length()];
	for (int i = 0; i < vector.Length(); i++)
	{
		stream >> str[i];

	}
	for (int i = 0; i < vector.Length(); i++)
	{
		if (str[i] != '0')
			vector[i] = 1;
		else
			vector[i] = 0;
	}
	delete[]str;
	return stream;
}

std::ostream& operator <<(std::ostream& stream,const BoolVector& vector)
{
	stream << "[";
	for (int j = 0; j < vector.m_length + vector.m_insignificantRankCount; j++)
	{
		if (j % 8 == 0 && j != 0)
			std::cout << "][";
		std::cout << (bool)vector[j] << " ";
	}
	stream << "]" << std::endl;
	return stream;
}

BoolVector::BoolRank& BoolVector::BoolRank::operator=(const BoolRank& other) {
	operator=((bool)other);
	return *this;
}

BoolVector::BoolRank& BoolVector::BoolRank::operator=(const bool value)
{
	if (value == 0)
		(*m_cell) &= ~m_mask;
	else
		(*m_cell) |= m_mask;
	return *this;
}

BoolVector::BoolRank::operator bool() const
{
	if (*m_cell & m_mask)
		return true;
	else
		return false;
}

const BoolVector::BoolRank BoolVector::operator[](const int index)const
{
	assert(index>=0);
	return BoolRank(m_cells + index / m_cellSize, index % m_cellSize);
}	

bool BoolVector::operator==(const BoolVector& other)const
{
	if (Length() != other.Length())
		return false;
	for (int i = 0; i < other.Length(); ++i)
	{
		if (operator[](i) != other[i])
			return false;
	}
	return true;
}

void BoolVector::Swap(int i, int j)
{
	assert(i >= 0 && i <= m_cellCount && j >= 0 && j <= m_cellCount);
	UC cell = m_cells[i];
	m_cells[i] = m_cells[j];
	m_cells[j] = cell;
}

const BoolVector::UC* BoolVector::getCells() const
{
	return m_cells;
}

void BoolVector::addSymbol(const UC symbol, int index)
{
	assert(index < m_cellCount);
	m_cells[index] = symbol;
}