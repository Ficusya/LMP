#pragma once
#include<iostream>
#include <fstream>
#include "Student.h"

using TInfo = Schet;

struct NODE
{
	TInfo info;
	NODE* next, *prev;
	NODE(TInfo info, NODE* next = nullptr, NODE* prev = nullptr) :
		info(info), next(next), prev(prev) {};
	~NODE()
	{
		next = nullptr;
		prev = nullptr;
	}
};
using ptrNODE = NODE*;

struct  DLIST
{
private:
	ptrNODE begin, end;
	size_t size;
public:
	DLIST() { begin = nullptr; end = nullptr; }
	DLIST(const char* filename);
	void first_node(const Schet& stud);
	bool empty();
	void add_after(ptrNODE ptr, const Schet& stud);
	void add_before(ptrNODE ptr, const Schet& stud);
	void del_before(ptrNODE& ptr);
	void del_after(ptrNODE& ptr);
	void print();
	~DLIST();
	Schet& Delete(ptrNODE& ptr);
	ptrNODE get_begin()
	{
		return begin;
	}
};