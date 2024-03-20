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

//void third_stage_breackdown(FileStruct& file, int i, std::vector<std::fstream> &fileVec);
//
//void second_stage_breakdown(FileStruct & file, int i, std::vector<std::fstream> &fileVec) {
//	int number_of_intmax = 0, number_before=INT_MIN, number_now;
//	file.fileStream >> number_now;
//	while (number_before <= number_now && file.fileStream) {
//		if (number_now == INT_MAX) {
//			number_of_intmax++;
//			number_before = number_now;
//			file.fileStream >> number_now;
//		}
//		else {
//			fileVec[i] << number_now << " ";
//			number_before = number_now;
//			file.fileStream >> number_now; 
//		}
//	}
//	file.ms[i]--;
//	if (!file.fileStream) {
//		if(number_before<=number_now) fileVec[i] << number_now << " ";
//		else {
//			if (file.ms[i] < file.ms[i + 1])	
//			fileVec[i+1] << number_now << " ";
//			else {
//				if (file.ms[i] == 0) {
//					file.L++;
//					int ip0 = file.ip[0];
//					i = 0;
//					for (int k = 0; k < file.filesCount - 1; k++) {
//						file.ms[k] = file.ip[k + 1] - file.ip[k] + ip0;
//						file.ip[k] = file.ip[k + 1] + ip0;
//					}
//					fileVec[i] << number_now << " ";
//				}
//				else fileVec[0] << number_now << " ";
//			}
//		}
//		for (int i = 0; i < file.filesCount - 1; i++)
//			fileVec[i].close();
//		file.fileStream.close();
//		return;
//	}
//	else {
//		// 3 stage
//		third_stage_breackdown(file,i,fileVec);
//	}
//}
//
//void third_stage_breackdown(FileStruct& file, int i, std::vector<std::fstream>& fileVec) {
//	if (file.ms[i] < file.ms[i + 1]) {
//		i++;
//		second_stage_breakdown(file,i, fileVec);
//	}
//	else {
//		if (file.ms[i] == 0) {
//			file.L++;
//			int ip0 = file.ip[0];
//			i = 0;
//			for (int k = 0; k < file.filesCount - 1; k++) {
//				file.ms[k] = file.ip[k + 1] - file.ip[k] + ip0;
//				file.ip[k] = file.ip[k + 1] + ip0;
//			}
//			second_stage_breakdown(file,i, fileVec);
//		}
//		else {
//			i = 0;
//			second_stage_breakdown( file, i, fileVec);
//
//		}
//	}
//}




void breakdown(FileStruct& file, std::vector<std::fstream*> &fileVec, std::ifstream &fileStream) {
	for (int i = 0; i < file.filesCount-1; i++) file.ms[i] = 1;

	for (int i = 0; i < file.filesCount - 1; i++) file.ip[i] = 1;

	file.ip[file.filesCount - 1] = 0;

	file.ms[file.filesCount - 1] = 0;

	file.L = 1;
	int	i = 0;

	fileStream.open(file.original);

	int  number_before = INT_MIN, number_now;
	fileStream >> number_now;
	while (fileStream) {
		if (number_now == INT_MAX) 
			file.number_of_intmax++;
		else {
			*fileVec[i] << number_now << " ";
		}

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
		if (file.ms[i] < file.ms[i + 1]) i++;
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
	for (int j = 0; j < file.filesCount; j++) {
		fileVec[i]->close();
	}
	fileStream.close();
}

void merger(FileStruct& file, std::vector<std::fstream*>& fileVec, std::ofstream& fileStream) {

	for (int k = 0; k < file.filesCount - 2; k++)
		fileVec[k]->open(file.fileName[k], std::ios::in);
	fileVec[file.filesCount - 1]->open(file.fileName[file.filesCount - 1], std::ios::out);
	bool mss = true;
	for (int i = 0; i < (file.filesCount - 1); i++)
	{
		if (mss && (file.ms[i] > 0)) mss = true;
		else
		{
			mss = false;
			break;
		}
	}
	while (file.L != 0)
	{
		while (file.ip[file.filesCount - 2] != 0) {
			std::vector<int> mergingFiles;
			while (mss)
			{
				for (int i = 0; i < (file.filesCount - 1); i++)
				{
					if (mss && (file.ms[i] > 0)) mss = true;
					else
					{
						mss = false;
						break;
					}
				}
				if (mss)
				{
					for (int i = 0; i < (file.filesCount - 1); i++)
						file.ms[i]--;
					file.ms[file.filesCount - 1]++;
				}
			}
			for (int i = 0; i < (file.filesCount - 1); i++)
			{
				if (file.ms[i] > 0) {
					file.ms[i]--;
					file.ip[i] = INT_MAX;
				}
				else
				{
					*fileVec[i] >> file.ip[i];
				}
			}
			int minEl = file.ip[0];
			int minInd = 0;
			while (minEl == INT_MAX && minInd < file.filesCount - 2) {
				minInd++;
				minEl = file.ip[minInd];
			}
			for (; minEl != INT_MAX;) {
				for (int i = 1; i < file.filesCount; i++) {
					minEl = std::min(minEl, file.ip[i]);
					if (minEl == file.ip[i]) minInd = i;
				}
				if (minEl == INT_MAX) break;
				*fileVec[file.filesCount - 1] << minEl << " ";
				*fileVec[mergingFiles[minInd]] >> file.ip[minInd];
			}
			*fileVec[file.filesCount - 1] << minEl << " ";
			file.L--;
			fileVec[file.filesCount - 2]->close();
			fileVec[file.filesCount - 1]->close();
			fileVec[file.filesCount - 1]->open(file.fileName[file.filesCount - 1], std::ios::in);
			fileVec[file.filesCount - 2]->open(file.fileName[file.filesCount - 2], std::ios::out);


			/*std::vector<int> input;
			for (int i = 0; i < mergingFiles.size(); i++) {
				int k;
				fileVec[mergingFiles[i]] >> k;
				input.push_back(k);
			}
			int minEl=input[0];
			int minInd=0;
			for (;;) {
				for (int i = 1; i < input.size(); i++) {
					minEl = std::min(minEl, input[i]);
					if (minEl == input[i]) minInd = i;
				}
				if (minEl == INT_MAX) break;
				fileVec[file.filesCount-1] << minEl<<" ";
				fileVec[mergingFiles[minInd]]>> input[minInd];
			}
			fileVec[file.filesCount - 1] << minEl << " ";*/
		}
	}
}

int main() {
	std::cout << "Enter the number of files:";
	FileStruct work_file;
	int max;
	std::cin >> work_file.filesCount;
	std::cout << std::endl;
	while (work_file.filesCount < 2) {
		std::cout << "Enter correct(>2) nomber of files" << std::endl;
		std::cin >> work_file.filesCount;
	}
	work_file.filesCount;
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
			std::vector<std::fstream*> fileVec;
			std::fstream* zero = nullptr;
			for (int k = 0; k < work_file.filesCount - 1; k++) {
				zero = new std::fstream(work_file.fileName[k]);
				zero->open(work_file.fileName[k], std::ios::out);
				fileVec.push_back(zero);
				zero->close();
			}
			std::ifstream fileStream;
			breakdown(work_file, fileVec, fileStream);
			/*std::ofstream fileStream2;
			merger(work_file, fileVec, fileStream2);*/
			break;
		}
		break;
	}
}