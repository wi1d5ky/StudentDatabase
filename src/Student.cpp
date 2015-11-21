#include "Student.h"
#include <iostream>

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
		std::cout << " " << _score[i];
	std::cout << std::endl;
}

void Student::Print()
{
	static_cast<const Student &>(*this).Print();
}

std::ostream & operator << (std::ostream &os, const Student &rhs)
{
	rhs.Print();
	return os;
}
