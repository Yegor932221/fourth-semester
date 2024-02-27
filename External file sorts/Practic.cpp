#include <stdio.h>
#include<iostream>
#include <fstream>
#include<string>
#include<vector>

//40 35 94 -1 15 59 20 14 71 -1 26 88 -1 -1 2 4 -1 -1 39 -1 10 83 34 -1 otrezok

int breakdown(const char* name,int n, std::ofstream files []) {
	int number_of_intmax=0,number_before,number_of_file=0,number_now;
	std::ifstream fin(name);
	if (!fin.good())
		std::cout << "File not found!" << std::endl;
	else
	{
		fin >> number_now;
		if (number_now == INT_MAX) {
			number_of_intmax++;
			number_before = INT_MIN;
		}
		else {
			files[number_of_file] << number_now;
			number_before = number_now;
		}
		while (fin >> number_now)
		{
			if (number_before > number_now) {
				files[number_of_file]<<INT_MAX;
				number_of_file = (number_of_file + 1) % n;
				files[number_of_file] << number_now;
			}
			if (number_now == INT_MAX) {
				number_of_intmax++;
				continue;
			}
			number_before = number_now;
		}
	}
	fin.close();
	return number_of_intmax;
}

int CopyArrayFromFile(const char* name, std::vector<int>& arr) {
	std::ifstream fin(name);

	int n,h=0,g;
	if (!fin.good())
		std::cout << "File not found!" << std::endl;
	else
	{
		fin >> n;
		if (n == INT_MAX) h++;
		arr.push_back(n);
		g = n;
		while (fin >> n)
		{
			if (n == INT_MAX) {
				h++;
				continue;
			}
			if (g>n) {
				arr.push_back(INT_MAX);
			}
			g=n;
			arr.push_back(n);	
		}
	}
	fin.close();
	return h;
}


int main() {
	std::cout << "Enter the number of files:";
	int n, max;
	std::cin >> n;
	std::cout << std::endl;
	std::ofstream* files = new std::ofstream[n];
	for (int i = 0; i < n; i++) {
		std::string name = "WorkFile" + std::to_string(i) + ".txt";
		const char* file = name.c_str();
		files[i].open(file);
		if (!files[i].is_open()) std::cout << "Error" << std::endl;
	}
	for (int range = 10; range <= 100000; range *= 100)
	{
		for (int size = 10000; size <= 1000000; size *= 10)
		{
			float time = 0;
			std::string name = "Shell" + std::to_string(size) + "_in_range_" + std::to_string(range) + ".txt";
			const char* starter_file = name.c_str();
			max = breakdown(starter_file,n, files);
			for (int i = 0; i < n; i++) {
				files[i].close();
			}

		}
	}
}