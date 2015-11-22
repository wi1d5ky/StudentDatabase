#include "Student.h"
#include <iomanip>
#include <Database.h>

Student::Student()
{
	setName("[NO NAME]").setAge(0).setGender('N');
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
		setScores(scores[i], i);
	return *this;
};

void Student::Print() const
{
	Print(stdout);
}

void Student::Print()
{
	static_cast<const Student &>(*this).Print();
}

void Student::Print(FILE* fp) const
{
	if(fp == nullptr)
	{
		std::cout << "Export Failed." << std::endl;
		return;
	}

	fprintf(fp, "%s %c (%d)", _name.c_str(), _gender, _age);
	for(int i = 0; i < scoreNum ; ++i)
		fprintf(fp, " %.2f", _score[i]);
	fprintf(fp, "\n");
}

void Student::Print(FILE* fp)
{
	return static_cast<const Student &>(*this).Print(fp);
}

std::ostream & operator << (std::ostream &os, const Student &rhs)
{
	rhs.Print();
	return os;
}

void obtain(FILE* fp, Database& database)
{
	Student newborn;
	char name[maxNameLength] = {};

	while(fscanf(fp, "%s %c (%d) ", name, &(newborn._gender), &(newborn._age)) != EOF)
	{
		newborn.setName(name);
		for(int i = 0 ; i< scoreNum ; ++i)
			fscanf(fp, " %f", &(newborn._score[i]));
		database.add(newborn);
	}
}
