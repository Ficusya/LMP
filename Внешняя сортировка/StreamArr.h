#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include "dataobj.h"

struct stor_str
{
	char data;
	int key;
	stor_str(char data = '\0', int key = 0) :data(data), key(key) {}
};

class streamArr
{
private:
	int size;
	int** data_cnt;
	std::fstream main_file;
	std::fstream** farr;
	int seq_length;
public:
	streamArr(int size, const char* m_file_name);
	~streamArr();
	void distribute();
	void rst_pos();
	int seq_merge(int src_half, int dst_num, int** buf);
	void merge(int src_half, int** buff);
	void sort();
	void copy(std::fstream& src, std::fstream& dst);
};