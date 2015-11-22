#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

constexpr int scoreNum = 3;
constexpr int maxNameLength = 30;

class Database;

class Student
{
public:
	Student();

	const std::string Name()
	{
		return _name;
	};
	const std::string Name() const
	{
		return _name;
	};

	Student& setName(std::string name);
	Student& setGender(char gender);
	Student& setAge(int age);
	Student& setScores(float score, int seq);
	Student& setScores(float scores[]);

	void Print();
	void Print() const;
	void Print(FILE* fp);
	void Print(FILE* fp) const;

	friend void obtain(FILE* fp, Database& database);
	friend std::ostream & operator << (std::ostream &os, const Student &rhs);

private:
	std::string _name = "[NO NAME]";
	char _gender = 'N';
	int _age = 0;
	float _score[scoreNum] = {0};
};

void obtain(FILE* fp, Database& database);

#endif // STUDENT_H
