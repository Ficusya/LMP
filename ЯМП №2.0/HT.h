#include<vector>
#include<iostream>
#include<algorithm>
#include"Student.h"

using P = std::pair<int, Schet>;
using THashTable = std::vector<P>;
using Iterator = THashTable::iterator;

#pragma once
class HashTable
{
private:
	THashTable hashTable;
	size_t maxSize;
public:
	HashTable() :maxSize(2)
	{
		hashTable.resize(maxSize);
	}
	HashTable(std::ifstream& file);
	void rehash();
	size_t hash(int key);
	Iterator find(int key);
	bool remove(int key);
	bool add(Schet S);
	void print();
	int count();
};
