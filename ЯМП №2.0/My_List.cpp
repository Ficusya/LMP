#include "My_List.h"
#include <functional>

ptrNODE find_place(ptrNODE begin, const Schet& stud)
{
	ptrNODE p = begin;
	while (p && p->info.compare(stud) < 0)
		p = p->next;
	return p;
}

DLIST::DLIST(const char* filename)
{
	std::ifstream file(filename);
	Schet stud(file);
	first_node(stud);
	ptrNODE place;
	while (!file.eof())
	{
		Schet stud(file);
		place = find_place(begin, stud);
		if (place)
			add_before(place, stud);
		else
			add_after(end, stud);

	}
	file.close();
}

void DLIST::first_node(const Schet& stud)
{
	begin = new NODE(stud);
	end = begin;
}

bool DLIST::empty()
{
	return begin == nullptr;
}

void DLIST::add_after(ptrNODE ptr, const Schet& stud)
{
	ptrNODE p = new NODE(stud, ptr->next, ptr);
	if (ptr == end)
		end = p;
	ptr->next = p;
}

void DLIST::add_before(ptrNODE ptr, const Schet& stud)
{
	ptrNODE p = new NODE(stud, ptr, ptr->prev);
	if (ptr == begin)
		begin = p;
	else
		ptr->prev->next = p;
	ptr->prev = p;
}

void DLIST::print()
{
	ptrNODE ptr = begin;
	while (ptr)
	{
		ptr->info.print();
		ptr = ptr->next;
	}
}

DLIST::~DLIST()
{
	while (!empty())
		Delete(begin);
}

Schet& DLIST::Delete(ptrNODE& ptr)
{
	ptrNODE p = ptr;
	if (ptr == begin)
	{
		begin = p->next;
		ptr = begin;
		if (p->next)
			p->next->prev = nullptr;
	}
	else
		if (ptr == end)
		{
			end = p->prev;
			ptr = end;
			if (p->prev)
				p->prev->next = nullptr;
		}
		else
		{
			ptr = ptr->next;
			p->next->prev = p->prev;
			p->prev->next = p->next;
		}
	static Schet stud;
	stud = p->info;
	delete p;
	return stud;
}

void DLIST::del_before(ptrNODE& ptr)
{
	if (ptr && ptr->prev)
	{
		if (ptr->prev == begin)
			begin = ptr;
		Delete(ptr->prev);
		--size;
	}
}

void DLIST::del_after(ptrNODE& ptr)
{
	if (ptr && ptr->next)
	{
		if (ptr->next == end)
			end = ptr;
		Delete(ptr->next);
		--size;
	}
}