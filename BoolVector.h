#pragma once
#include<stdint.h>
#include<vector>
#include<iostream>

class BoolVector
{
	using UI = unsigned int;
	using UC = unsigned char;

private:
	UI m_length = 0;
	UI m_cellCount = 0;
	uint8_t m_insignificantRankCount = 0;
	UC* m_cells = nullptr;
	static const uint8_t m_cellSize = 8;

public:
	BoolVector();
	BoolVector(UI length, const bool value=false);
	~BoolVector();
	int Length()const;
	BoolVector(std::vector<bool>& vec);
	BoolVector(const BoolVector& other);
	void Set1(const int cell, const int pos_cell);
	void Set0(const int cell, const int pos_cell);
	BoolVector(const char* str);
	void Swap(BoolVector& other);
	BoolVector operator<<(const int count)const;
	BoolVector operator>>(const int count)const;
	void Invert();
	void InvertElement(int index);	
	void Set1InRange(int index, const int rangó=1);
	void Set0InRange(int index, const int range=1);
	void Set1All();
	void Set0All();
	int Weight() const;
	void Swap(int i, int j);
	class BoolRank;

	BoolVector::BoolRank operator[](const int index);
	const BoolVector::BoolRank operator[](const int index)const;

	BoolVector operator&(const BoolVector& other)const;
	BoolVector operator&=(const BoolVector& other);
		
	BoolVector operator^(const BoolVector& other)const;
	BoolVector operator^=(const BoolVector& other);

	BoolVector operator|(const BoolVector& other)const;
	BoolVector operator|=(const BoolVector& other);

	BoolVector operator<<=(const int count);
	BoolVector operator>>=(const int count);

	BoolVector operator ~()const;
	bool operator==(const BoolVector& other) const;

	BoolVector& operator=(const BoolVector& other);
	friend	std::ostream& operator <<(std::ostream& stream, const BoolVector& vector);
	const UC* getCells() const;
	void addSymbol(const UC symbol, int index);
	void toString(const BoolVector* vector);
};

class BoolVector::BoolRank
{
private:
	uint8_t* m_cell = nullptr;
	uint8_t m_mask = 1 << 7;
public:
	void Print();
	BoolRank(UC* cell, const int mask);
	BoolRank& operator=(const BoolRank& other);
	BoolRank& operator=(const bool value);
	operator bool() const;
};

std::istream& operator >>(std::istream& stream, BoolVector& vector);