#pragma once
#include<string>
#include<iostream>
#include<fstream>

struct Schet
{
private:
	int number, date; //номер и дата
	std::string name, type; //Заказчик и вид (расход/приход)
	int  summ;  //сумма по счету
public:
	Schet() {}
	Schet(std::ifstream& file);
	void print();
	int compare(const Schet& stud);
	int kind();
	int get_number()
	{
		return number;
	}
	int get_date()
	{
		return date;
	}
};
