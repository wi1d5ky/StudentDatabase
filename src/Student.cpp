#include "Student.h"
#include "Database.h"
#include <iomanip>
#include <cstdio>
#include <cstring>

Student& Student::setName(std::string name)
{
	name_ = name;
	return *this;
};
Student& Student::setAge(int age)
{
	age_ = age;
	return *this;
};
Student& Student::setGender(char gender)
{
	gender_ = gender;
	return *this;
};
Student& Student::setScores(float score, int seq)
{
	score_[seq] = score;
	return *this;
};
Student& Student::setScores(float scores[])
{
	for(int i = 0; i < scoreNum; ++i)
		setScores(scores[i], i);
	return *this;
};

void Student::print() const
{
	exportTo(stdout);
}

void Student::exportTo(FILE* fp) const
{
	if(fp == nullptr)
	{
		std::cout << "Export Failed." << std::endl;
		return;
	}

	fprintf(fp, "%s %c (%d)", name_.c_str(), gender_, age_);
	for(int i = 0; i < scoreNum ; ++i)
		fprintf(fp, " %.2f", score_[i]);
	fprintf(fp, "\n");
}

std::ostream & operator << (std::ostream &os, const Student &rhs)
{
	rhs.print();
	return os;
}

void obtain(FILE* fp, Database& database)
{
	Student newborn;
	char name[maxNameLength] = {};

	while(fscanf(fp, "%s %c (%d) ", name, &(newborn.gender_), &(newborn.age_)) != EOF)
	{
		if(strcmp(name, "<Empty>") == 0)
			break;
		newborn.setName(name);
		for(int i = 0 ; i< scoreNum ; ++i)
			fscanf(fp, " %f", &(newborn.score_[i]));
		database.add(newborn);
	}
}
