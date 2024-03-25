#include <stdio.h>
#include<iostream>
#include <fstream>
#include<string>
#include<vector>

struct FileStruct
{
	int number_of_intmax = 0;
	int filesCount;
	std::string original;
	std::string* fileName = nullptr;
	int* ip = nullptr;
	int* ms = nullptr;
	int L = 0;
	int* sliv = nullptr;
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


int MinIndex(int* arr, int n) {
	int minIndex, min, f;
	minIndex = 0;
	min = arr[0];
	for (int i = 1; i <= n - 2; ++i)
	{
		f = arr[i];
		if (f < min)
		{
			min = f;
			minIndex = i;
		}
	}
	return minIndex;
}


void breakdown(FileStruct& file, std::vector<std::fstream*> &fileVec, std::ifstream &fileStream) {
	for (int k = 0; k < file.filesCount - 1; k++) {
		fileVec[k]->open(file.fileName[k], std::ios::out);
	}

	for (int i = 0; i < file.filesCount - 1; i++)
	{
		file.ms[i] = 1;
		file.ip[i] = 1;
		file.sliv[i] = INT_MAX;
	}
	file.ip[file.filesCount - 1] = 0;
	file.sliv[file.filesCount - 1] = INT_MAX;
	file.ms[file.filesCount - 1] = 0;

	file.L = 1;
	int	i = 0;

	fileStream.open(file.original);

	int  number_before = INT_MIN, number_now;
	fileStream >> number_now;
	while (!fileStream.eof()) {
		while (number_now == INT_MAX) {
			file.number_of_intmax++;
			fileStream >> number_now;
		}
		*fileVec[i] << number_now << " ";

		number_before = number_now;
		fileStream >> number_now;

		while ((!fileStream.eof()) && (number_before <= number_now)) {
			number_before = number_now;

			if (number_now == INT_MAX)
				file.number_of_intmax++;
			else {
				*fileVec[i] << number_now << " ";
			}
			fileStream >> number_now;
		}
		file.ms[i]--;
		*fileVec[i] << INT_MAX << " ";
		if (file.ms[i] < file.ms[i+1]) i++;
		else {
			if (file.ms[i] == 0) {
				file.L++;
				int ip0 = file.ip[0];
				i = 0;
				for (int k = 0; k < file.filesCount - 1; k++) {
					file.ms[k] = file.ip[k + 1] - file.ip[k] + ip0;
					file.ip[k] = file.ip[k + 1] + ip0;
				}
			}
			else i = 0;
		}
		number_before = number_now;
		if (fileStream.eof() && number_now != INT_MAX) {
			*fileVec[i] << number_before << " " << INT_MAX;
			file.ms[i]--;
		}
	}
	for (int j = 0; j < file.filesCount-1; j++) {
		fileVec[i]->close();
	}
	fileStream.close();
}

void merger(FileStruct& file, std::vector<std::fstream*>& fileVec, std::ofstream& fileStream) {

	for (int k = 0; k < file.filesCount - 2; k++)
		fileVec[k]->open(file.fileName[k], std::ios::in);
	fileVec[file.filesCount - 1]->open(file.fileName[file.filesCount - 1], std::ios::out);
	
	while (file.L != 0){
		while (*fileVec[file.filesCount - 2] >> file.ip[file.filesCount - 2]) {
			bool allms = true;
			for (int i = 0; i < (file.filesCount - 1); i++)
			{
				if (file.ms[i] <= 0) allms = false;
			}

			while (allms)
			{
				for (int i = 0; i < (file.filesCount - 1); ++i)
				{
					--file.ms[i];
					if (file.ms[i] <= 0) allms = false;
				}
				file.ms[file.filesCount - 1]++;
			}
			for (int i = 0; i < (file.filesCount - 1); ++i)
			{
				if (file.ms[i] == 0) {
					if (i == file.filesCount - 2)
						continue;
					*fileVec[i] >> file.ip[i];
				}

				else
				{ 
					if (file.ms[i] > 0)
					{
						if (i == file.filesCount - 2)
						{
							fileVec[file.filesCount - 2]->close();
							fileVec[file.filesCount - 2]->open(file.fileName[file.filesCount - 2], std::ios::in);
						}
						--file.ms[i];
						file.ip[i] = INT_MAX;
					}
				}
			}
			for (; ;)
			{
				int indexMin = MinIndex(file.ip,file.filesCount);
				if (file.ip[indexMin] == INT_MAX)
					break;
				*fileVec[file.filesCount - 1] << file.ip[indexMin] << " ";
				*fileVec[indexMin] >> file.ip[indexMin];
			}
			if (file.L != 1)
			{
				*fileVec[file.filesCount - 1] << INT_MAX << " ";
			}
			else
			{
				for (int i = file.filesCount; i > 0; --i)
				{
					*fileVec[file.filesCount - 1] << INT_MAX << " ";
				}
			}
			file.L--;
			file.ip[file.filesCount - 1]++;
			fileVec[file.filesCount - 2]->close();
			fileVec[file.filesCount - 1]->close();
			fileVec[file.filesCount - 1]->open(file.fileName[file.filesCount - 1], std::ios::in);
			fileVec[file.filesCount - 2]->open(file.fileName[file.filesCount - 2], std::ios::out);
			for (int i = file.filesCount - 1; i > 0; i--)
			{
				std::swap(file.fileName[i], file.fileName[i - 1]);
				std::swap(fileVec[i], fileVec[i - 1]);
				std::swap(file.ms[i], file.ms[i - 1]);
				std::swap(file.ip[i], file.ip[i - 1]);
			}
		}
	}
}




int main() {
	FileStruct work_file;
	int max;
	work_file.filesCount=4;
	work_file.fileName = CreateFiles(work_file.filesCount);
	for (int range = 10; range <= 100000; range *= 100)
	{
		for (int size = 10000; size <= 1000000; size *= 10)
		{
			//std::string name = "Shell" + std::to_string(size) + "_in_range_" + std::to_string(range) + ".txt";
			std::string name = "Small.txt";
			work_file.original = name.c_str();
			work_file.ip = new int[work_file.filesCount];
			work_file.ms = new int[work_file.filesCount];
			work_file.sliv = new int[work_file.filesCount];
			std::vector<std::fstream*> fileVec;
			std::fstream* zero = nullptr;
			for(int k = 0; k < work_file.filesCount; k++) {
				zero = new std::fstream(work_file.fileName[k]);
				zero->open(work_file.fileName[k], std::ios::out);
				fileVec.push_back(zero);
				zero->close();
			}

			std::ifstream fileStream;
			breakdown(work_file, fileVec, fileStream);
			std::ofstream fileStream2;
			merger(work_file, fileVec, fileStream2);
			break;
		}
		break;
	}
}