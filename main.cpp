#include <iostream>
#include "HashTable.h"
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>
#include <assert.h>

int main()
{
	FirstHashFunction first;
	SecondHashFunction second;
	ThirdHashFunction third;
	HashTable<std::string> table1;
	HashTable<std::string> table2(&second, 10);
	HashTable<std::string> table3(&third, 10);
	
	table1.AddEl(5, "zxc");
	table1.AddEl(21, "df");
	table1.AddEl(12, "egor");
	table1.AddEl(41, "gg");
	table1.AddEl(3, "ez");
	std::cout << std::endl << "first before erase df" << std::endl;
	table1.Print();
	table1.Erase(21);
	std::cout << std::endl << "first after erase df" << std::endl;
	table1.Print();
	std::cout << std::endl << "first after change hash function" << std::endl;
	table1.ChangeHashFunction(&third);
	table1.Print();
	if (table1.Contains(3))
		std::cout << "Contains work1" << std::endl;
	if (!table1.Contains(4))
		std::cout << "Contains work2" << std::endl;

	std::cout<< std::endl << "second"<<std::endl;
	table2.AddEl(5, "zxc");
	table2.AddEl(21, "df");
	table2.AddEl(12, "egor");
	table2.AddEl(41, "gg");
	table2.AddEl(3, "ez");
	table2.Print();
	std::cout<<std::endl<<"element index 21 " << table2[21]<<std::endl;
	std::cout << std::endl << "third" << std::endl;
	table3.AddEl(5, "zxc");
	table3.AddEl(21, "df");
	table3.AddEl(12, "egor");
	table3.AddEl(41, "gg");
	table3.AddEl(3, "ez");
	table3.Print();
	std::cout << std::endl << "first after =second" << std::endl;
	table1 = table2;
	table1.Print();
	return 0;
}