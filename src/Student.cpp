#include "Student.h"
#include <iostream>
#include <iomanip>

Student::Student()
{
	setName("[NO NAME]");
	setAge(0);
	setGender('N');
	for(int i = 0 ; i < scoreNum ; ++i)
		setScores(0, i);
};
Student& Student::setName(std::string name)
{
	_name = name;
	return *this;
};
Student& Student::setAge(int age)
{
	_age = age;
	return *this;
};
Student& Student::setGender(char gender)
{
	_gender = gender;
	return *this;
};
Student& Student::setScores(float score, int seq)
{
	_score[seq] = score;
	return *this;
};
Student& Student::setScores(float scores[])
{
	for(int i = 0; i < scoreNum; ++i)
		_score[i] = scores[i];
	return *this;
};

void Student::Print() const
{
	std::cout<< _name << " " << _gender << " (" << _age << ")";
	for(int i = 0; i < scoreNum ; ++i)
		std::cout << " " << std::fixed << std::setprecision(2) << _score[i];
	std::cout << std::endl;
}

void Student::Print()
{
	static_cast<const Student &>(*this).Print();
}

bool Student::Print(FILE* fp) const
{
	if(fp == nullptr)
	{
		std::cout << "Export Failed." << std::endl;
		return false;
	}

	fprintf(fp, "%s %c (%d)", _name.c_str(), _gender, _age);
	for(int i = 0; i < scoreNum ; ++i)
		fprintf(fp, " %.2f", _score[i]);
	fprintf(fp, "\n");
	return true;
}

bool Student::Print(FILE* fp)
{
	return static_cast<const Student &>(*this).Print(fp);
}

std::ostream & operator << (std::ostream &os, const Student &rhs)
{
	rhs.Print();
	return os;
}
