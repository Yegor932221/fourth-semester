#include <stdio.h>
#include<iostream>
#include <fstream>
#include<string>
#include<vector>


struct FileStruct
{
	int filesCount;
	std::string original;
	std::string* fileName = nullptr;
	std::fstream fileStream;
	int* ip = nullptr;
	int* ms = nullptr;
	int L = 0;
};

std::string* CreateFiles(int filesCount)
{
	std::string* fileName = new std::string[filesCount];
	for (int i = 0; i < filesCount; ++i)
	{
		std::string name = "WorkFile" + std::to_string(i) + ".txt";
		fileName[i] = name;
		std::ofstream file(name);
		file.close();
	}
	return fileName;
}

void third_stage_breackdown(FileStruct& file, int i, std::vector<std::fstream> fileVec);

void second_stage_breakdown(FileStruct & file, int i, std::vector<std::fstream> fileVec) {
	int number_of_intmax = 0, number_before=INT_MIN, number_now;
	file.fileStream >> number_now;
	while (number_before <= number_now) {
		if (number_now == INT_MAX) {
			number_of_intmax++;
			number_before = INT_MIN;
			file.fileStream >> number_now;
		}
		else {
			fileVec[i] << number_now << " ";
			number_before = number_now;
			file.fileStream >> number_now;
		}
	}
	file.ms[i]--;
	if (!file.fileStream) {
		for (int i = 0; i < file.filesCount - 1; i++)
			fileVec[i].close();
		file.fileStream.close();
	}
	else {
		// 3 stage
		third_stage_breackdown(file,i,fileVec);
	}
}

void third_stage_breackdown(FileStruct& file, int i, std::vector<std::fstream> fileVec) {
	if (file.ms[i] < file.ms[i + 1]) {
		i++;
		second_stage_breakdown(file,i, fileVec);
	}
	else {
		if (file.ms[i] == 0) {
			file.L++;
			int ip0 = file.ip[0];
			i = 0;
			for (int k = 0; k < file.filesCount - 1; k++) {
				file.ms[k] = file.ms[k + 1] - file.ip[k] + ip0;
				file.ip[k] = file.ip[k + 1] + ip0;
			}
			second_stage_breakdown(file,i, fileVec);
		}
		else {
			i = 0;
			second_stage_breakdown( file, i, fileVec);

		}
	}
}


void breakdown(FileStruct& file) {
	for (int i = 0; i < file.filesCount-1; i++) file.ms[i] = 1;

	for (int i = 0; i < file.filesCount - 1; i++) file.ip[i] = 1;

	file.ip[file.filesCount - 1] = 0;

	file.ms[file.filesCount - 1] = 0;

	file.L = 1;
	int	i = 0;

	std::fstream foo;
	foo.open(file.original, std::ios::in);
	file.fileStream.swap(foo);

	std::vector<std::fstream> fileVec;
	for (int k = 0; k < file.filesCount - 1; k++)
		fileVec.push_back(std::fstream(file.fileName[k], std::ios::out));
	//2 stage
	second_stage_breakdown( file,i,fileVec);
	
}


int main() {
	std::cout << "Enter the number of files:";
	FileStruct work_file;
	int max;
	std::cin >> work_file.filesCount;
	std::cout << std::endl;
	work_file.fileName = CreateFiles(work_file.filesCount);
	for (int range = 10; range <= 100000; range *= 100)
	{
		for (int size = 10000; size <= 1000000; size *= 10)
		{
			std::string name = "Shell" + std::to_string(size) + "_in_range_" + std::to_string(range) + ".txt";
			work_file.original = name.c_str();
			work_file.ip = new int[work_file.filesCount];
			work_file.ms = new int[work_file.filesCount];
			breakdown(work_file);
			
		}
	}
}