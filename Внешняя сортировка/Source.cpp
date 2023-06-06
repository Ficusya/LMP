#include <fstream>
#include <iostream>
#include <Windows.h>
#include "data.h"
#include "Sequence.h"
#include <map>
#include <string>

const int number_of_files = 3;

void Create_File(std::string filename, int cnt)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);
	srand(GetTickCount64());
	stor_str tmp;
	for (int i = 0; i < cnt; ++i)
	{
		tmp.key = rand() % 100;
		tmp.data = rand() % 100;
		file.write((char*)&tmp, sizeof(stor_str));
	}
	file.close();
}

bool  CheckFile(std::string filename)
{
	std::ifstream file(filename, std::ios::in | std::ios::binary);
	stor_str x, y;
	bool check(true);
	bool eof = false;
	while (!file.eof() && check)
	{
		x = y;
		eof = (bool)file.read((char*)&y, sizeof(stor_str));
		check = x.key <= y.key;
	}
	file.close();
	return check;
}

void Print(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary);

	if (!file) {
		std::cout << "Failed to open the file." << std::endl;
		return;
	}

	stor_str number;
	while (file.read((char*)&number, sizeof(stor_str)))
	{
		std::cout << number.key << ' ';
	}
	std::cout << std::endl;
	file.close();
}


void Distribute(Sequence& f0, std::string filename, Sequence f[number_of_files], std::map<int, int> Q)
{
	f0.StartRead(filename);
	for (int i = 0; i < number_of_files; ++i)
	{
		std::string name = "f" + std::to_string(i) + ".txt";
		f[i].StartWrite(name);
	}

	int ord = 0;

	while (!f0.eof)
	{
		f[Q[ord]].CopyRun(f0);
		ord = (ord + 1) % number_of_files;
	}
	f0.Close();
	for (int i = 0; i < number_of_files; ++i)
	{
		f[i].Close();
	}
}


void Merge(Sequence& f0, std::string filename, Sequence f[number_of_files], std::map<int, int> Q)
{

	f0.StartWrite(filename);
	for (int i = 0; i < number_of_files; ++i)
	{
		std::string name = "f" + std::to_string(i) + ".txt";
		f[i].StartRead(name);
	}

	size_t arr[number_of_files];
	int files_left_without_eof(number_of_files);
	int files_left_without_eor(number_of_files);
	int MinElem;
	for (int i = 0; i < files_left_without_eof;)
	{
		if (f[Q[i]].eof)
		{
			std::swap(Q[i], Q[files_left_without_eof - 1]);
			files_left_without_eof--;
		}
		else
			i++;
	}
	while (files_left_without_eof != 0)
	{
		files_left_without_eor = files_left_without_eof;
		for (int i = 0; i < files_left_without_eof; ++i)
		{
			arr[i] = 0;
		}

		while (files_left_without_eor != 0)
		{
			MinElem = 0;
			for (int i = 0; i < files_left_without_eor; ++i)
			{
				if (f[Q[MinElem]].elem.key > f[Q[i]].elem.key)
				{
					MinElem = i;
				}
			}
			f0.Copy(f[Q[MinElem]]);
			arr[Q[MinElem]]++;
			if (arr[Q[MinElem]] == f[Q[MinElem]].seria || f[Q[MinElem]].eof)
			{
				std::swap(Q[MinElem], Q[files_left_without_eor - 1]);
				--files_left_without_eor;
			}
		}
		for (int i = 0; i < files_left_without_eof;)
		{
			if (f[Q[i]].eof)
			{
				std::swap(Q[i], Q[files_left_without_eof - 1]);
				files_left_without_eof--;
			}
			else
				i++;
		}
	}

	f0.Close();
	for (int i = 0; i < number_of_files; ++i)
	{
		f[i].Close();
	}
}

void Sorting(std::string filename, size_t n)
{
	Sequence f0, f[number_of_files];
	std::map<int, int> Q;
	for (int i = 0; i < number_of_files; ++i)
	{
		Q[i] = i;
	}
	f0.seria = 1;
	do
	{
		Distribute(f0, filename, f, Q);
		Merge(f0, filename, f, Q);
		f0.seria *= number_of_files;
		for (int i = 0; i < number_of_files; ++i)
			f[i].seria *= number_of_files;
	} while (f0.seria < n);
	remove("f1.txt");
	for (int i = 0; i < number_of_files; ++i)
	{
		std::string name = "f" + std::to_string(i) + ".txt";
		remove("name");
	}
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	size_t n = 10;
	Create_File("data.txt", n);
	Print("data.txt");
	Sorting("data.txt", n);
	Print("data.txt");
	if (CheckFile("data.txt"))
		std::cout << "File is ordered";
	else
		std::cout << "Not ordered";

	std::cin.get();
	return 0;
}
