#include <iostream>
#include <Windows.h>
#include <fstream>
#include "StreamArr.h"



using std::cout;

const int file_count = 5;
const int num_count = 1000;

bool Check_File(std::string filename);
void Create_File(std::string filename, int cnt);

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	std::string test = "tst.srt";
	Create_File(test, num_count);
	streamArr sort_arr(file_count, test.c_str());
	sort_arr.sort();
	if (Check_File(test))

		cout << "Sorted\n";
	else
		cout << "Не sorted\n";
	std::cin.get();
}

void Create_File(std::string filename, int cnt)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary);
	srand(GetTickCount64());
	stor_str tmp;

	for (int i = 0; i < cnt; ++i)
	{
		tmp.key = rand()/* % 1000*/;
		tmp.data = rand() % 100;
		file.write((char*)&tmp, sizeof(stor_str));
		//cout << tmp.key << '\n';
	}
	file.close();
	//cout << "\n\n";
}

bool Check_File(std::string filename)
{
	std::ifstream file(filename, std::ios::in | std::ios::binary);
	stor_str x, y;
	bool check = true;
	bool eof = false;
	file.read((char*)&y, sizeof(stor_str));
	while (!file.eof() && check)
	{
		x = y;
		eof = (bool)file.read((char*)&y, sizeof(stor_str));
		check = x.key <= y.key;
		//cout << x.key << '\n';
	}
	file.close();
	return check;
}