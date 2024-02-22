#include <stdio.h>
#include<iostream>
#include <fstream>
#include<string>
#include<vector>
void breakdown(std::fstream& file0, std::fstream& file1, std::fstream& file2);
void merger(std::fstream& file0, std::fstream& file1, std::fstream& file2);

int main() {
	for (int range = 10; range <= 100000; range *= 100)
	{
		for (int size = 10000; size <= 1000000; size *= 10)
		{
			float time = 0;
			FILE* mass;
			std::vector<int> arr;
			std::string name = "Shell" + std::to_string(size) + "_in_range_" + std::to_string(range) + ".txt";
			const char* file = name.c_str();
			std::fstream fileStream(file);
			std::fstream file0("file0.txt");
			std::fstream file1("file1.txt");
			std::fstream file2("file2.txt");
			if (!fileStream.is_open()/* || !file0.is_open() || !file1.is_open() || !file2.is_open()*/) {
				return -1;
			}
			int value;
			fileStream >> value;
			while (!fileStream.eof()) {
				file2 << value;
				fileStream >> value;
			}
			std::cout << std::endl << "copy" << std::endl;
			breakdown(file0, file1, file2);
			std::cout << "breaked" << std::endl;


			_fcloseall();
		}
	}
}

void breakdown(std::fstream& file0, std::fstream& file1, std::fstream& file2){
	int value1, value2;
	file2 >> value1;
	if (!file2.eof()) return;
	file0 << value1;
	file2 >> value2;
	while (!file2.eof()) {
		while (!file2.eof() || value1 <= value2) {
			file0 << value2<<" ";
			file2 >> value1;
			std::swap(value1, value2);
		}
		file1 << value2 << "/ ";
		file2 >> value1;
		std::swap(value1, value2);
		while(!file2.eof() || value1 <= value2)
		{
			file1 << value2<< " ";
			file2 >> value1;
			std::swap(value1, value2);
		}
		file0 << value2<< "/ ";
		file2 >> value1;
		std::swap(value1, value2);
	}
}

void merger(std::fstream& file0, std::fstream& file1, std::fstream& file2) {
	int x, y;
	file0 >> x;
	file1 >> y;
	while (!file0.eof() || !file1.eof()) {
		if (x < y) {
			file2 << x;
			file0>> x;
		}
		else {
			file2 << y;
			file1>> y;
		}
	}
	while (!file0.eof()) {
		file2 << x;
		file0 >> x;
	}
	while (!file1.eof()) {
		file2 << y;
		file1 >> y;
	}
}