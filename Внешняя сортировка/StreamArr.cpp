#include "StreamArr.h"

streamArr::streamArr(int size, const char* m_file_name) :size(size)
{
	seq_length = 1;
	main_file.open(m_file_name, std::ios::binary | std::ios::in | std::ios::out);
	data_cnt = new int* [2];
	for (int i = 0; i < 2; i++)
		data_cnt[i] = new int[size];

	for (int j = 0; j < 2; j++)
		for (int i = 0; i < size; i++)
			data_cnt[j][i] = 0;

	farr = new std::fstream * [2];
	for (int i = 0; i < 2; i++)
		farr[i] = new std::fstream[size];

	std::string tmp;
	std::ofstream tmpstream;
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < size; i++)
		{
			tmp = (std::string)"file" + std::to_string(j + 1) + '_' + std::to_string(i + 1) + ".tmp";
			tmpstream.open(tmp.c_str());
			tmpstream.close();
			farr[j][i].open(tmp.c_str(), std::ios::binary | std::ios::in | std::ios::out);
		}
}

streamArr::~streamArr()
{
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < size; i++)
			farr[j][i].close();

	for (int j = 0; j < 2; j++)
	{
		delete[] farr[j];
		delete[] data_cnt[j];
	}
	delete[] farr;
	delete[] data_cnt;

	std::string tmp;
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < size; i++)
		{
			tmp = (std::string)"file" + std::to_string(j + 1) + '_' + std::to_string(i + 1) + ".tmp";
			remove(tmp.c_str());
		}
}

void streamArr::distribute()
{
	stor_str tmp;
	int i = 0;
	while (main_file.read((char*)&tmp, sizeof(stor_str)))
	{
		farr[0][i].write((char*)&tmp, sizeof(stor_str));
		++data_cnt[0][i];
		i = (i + 1) % size;
	}
	main_file.clear();
	main_file.seekg(0);
}

void streamArr::rst_pos()
{
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < size; i++)
		{
			farr[j][i].flush();
			farr[j][i].seekp(0);
		}
}

int streamArr::seq_merge(int src_half, int dst_num, int** buf)//int** buf(buf[size][2])(buf[...][0] - номер в elems, buf[...][1] - кол-во ост. элементов)
{
	stor_str* elems = new stor_str[size];
	int end = size - 1;

	for (int i = 0; i < size && end == size - 1; i++)
	{
		buf[i][0] = i;
		buf[i][1] = std::min(data_cnt[src_half][i], seq_length);

		if (buf[i][1])
			farr[src_half][i].read((char*)&elems[i], sizeof(stor_str));
		else
			end = i - 1;
	}

	int min = 0, min_num = -1, j = 0;
	int tmp = (src_half) ? 0 : 1;
	int merged_cnt = 0;

	while (end != -1)
	{
		min_num = -1;
		for (int i = 0; i <= end; i++)
		{
			if (buf[i][1] && (elems[buf[i][0]].key < min || min_num == -1))
			{
				min = elems[buf[i][0]].key;
				min_num = buf[i][0];
				j = i;
			}
		}

		(bool)farr[tmp][dst_num].write((char*)&elems[min_num], sizeof(stor_str));
		merged_cnt++;

		if (buf[j][1] > 1)
		{
			buf[j][1] -= 1;
			farr[src_half][min_num].read((char*)&elems[min_num], sizeof(stor_str));
		}
		else
		{
			buf[j][1] = 0;
			std::swap(buf[j], buf[end--]);
		}
	}
	delete[] elems;
	return merged_cnt;
}

void streamArr::merge(int src_half, int** buff)
{
	int dst_num = 0;
	int dst_half = (src_half) ? 0 : 1;
	while (data_cnt[src_half][0])
	{
		data_cnt[dst_half][dst_num] += seq_merge(src_half, dst_num, buff);
		dst_num = (dst_num + 1) % size;

		for (int i = 0; i < size; i++)
			/*data_cnt[src_half][i] = (data_cnt[src_half][i] > seq_length) ? data_cnt[src_half][i] - seq_length : 0;*/
			data_cnt[src_half][i] = std::max(data_cnt[src_half][i] - seq_length, 0);
	}
	rst_pos();
}

void streamArr::sort()
{
	std::function<bool(int)> check = [this](int dst_half) {
		bool result = false;
		if (data_cnt[dst_half][0])
		{
			result = true;
			int i = 1;
			while (i < size && result)
				if (data_cnt[dst_half][i++] != 0)
					result = false;
		}
		return result;
	};

	int src_half = 1, dst_half = 0;
	int** buff = new int* [size];
	for (int i = 0; i < size; i++)
		buff[i] = new int[2];

	distribute();
	rst_pos();

	do
	{
		std::swap(src_half, dst_half);
		merge(src_half, buff);
		seq_length *= size;
	} while (!check(dst_half));

	copy(farr[dst_half][0], main_file);
	main_file.close();

	for (int i = 0; i < size; i++)
		delete[] buff[i];
	delete[] buff;
}

void streamArr::copy(std::fstream& src, std::fstream& dst)
{
	stor_str temp('a', 0);
	src.clear();
	dst.clear();
	src.seekp(0);
	dst.seekp(0);
	while (src.read((char*)&temp, sizeof(stor_str)))
		dst.write((char*)&temp, sizeof(stor_str));
}
