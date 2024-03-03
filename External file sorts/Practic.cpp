#include <stdio.h>
#include<iostream>
#include <fstream>
#include<string>
#include<vector>

//40 35 94 -1 15 59 20 14 71 -1 26 88 -1 -1 2 4 -1 -1 39 -1 10 83 34 -1 otrezok

int* breakdown(const char* name,int n, std::fstream files [], int* ms) {
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
			files[number_of_file] << number_now << " ";
			number_before = number_now;
		}
		while (fin >> number_now)
		{
			if (number_before > number_now) {
				files[number_of_file] << INT_MAX << " ";
				ms[number_of_file]++;
				number_of_file = (number_of_file + 1) % n;
				files[number_of_file] << number_now << " ";
			}
			else {
				if (number_now == INT_MAX) {
					number_of_intmax++;
					
				}
				else {
					files[number_of_file] << number_now << " ";
				}
			}
			number_before = number_now;
		}
		files[number_of_file] << INT_MAX<< " ";
	}
	ms[number_of_file]++;
	int golden_max = ms[0];
	int* golden = new int[n];
	for (int l = 0; l < n; l++) golden[l] = 0;
	golden[n - 1] = 1;
	while (golden[n] < golden_max) {
		int h = golden[n];
		for (int a = 1; n - a >= 0; a++) 
		{
			golden[n] += golden[n - a];
		}
		for (int a = 1; n - a > 1; a++) 
		{
			golden[n - a - 1] = golden[n - a];
		}
	}
	int* ip = new int[n];
	for (int a = 0; a < n; a++) {
		ip[a] = golden[a] - ms[a];
	}

	fin.close();
	for (int i = 0; i < n; i++) {
		files[i].close();
	}
	return ip;
}

void merger(int*ip,int n, std::fstream files[]) {
	for()

}

int main() {
	std::cout << "Enter the number of files:";
	int n, max;
	std::cin >> n;
	std::cout << std::endl;
	std::fstream* files = new std::fstream[n];
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
			int *ms =new int [n];
			for (int i = 0; i < n; i++) ms[i] = 0;
			float time = 0;
			std::string name = "Shell" + std::to_string(size) + "_in_range_" + std::to_string(range) + ".txt";
			const char* starter_file = name.c_str();
			int* ip = new int[n];
			ip=breakdown(starter_file,n, files, ms);
			
		}
	}
}