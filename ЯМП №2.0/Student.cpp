#include "Student.h"
#pragma once

Schet::Schet(std::ifstream& file)
{
	file >> number;
	file >> date;
	file >> name;
	file >> type;
	file >> summ;
	file.ignore();
	std::string delim_line;
	std::getline(file, delim_line);
}

void Schet::print()
{
	std::cout << number << '\n';
	std::cout << date << '\n';
	std::cout << name << '\n';
	std::cout << type << '\n';
	std::cout << summ << '\n';
	std::cout << "-------------\n";
}

int Schet::compare(const Schet& stud)
{
	int result = 1;
	if (date < stud.date)
		result = -1;
	else
		if (number == stud.number && date == stud.date && name == stud.name && type == stud.type)
			result = 0;
	return result;
}

int Schet::kind()
{
	int result = 0;
	if (type == "ras")
		result = -summ;
	else result = summ;
	return result;
}
