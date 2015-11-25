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

	const std::string Name()
	{
		return name_;
	};
	const std::string Name() const
	{
		return name_;
	};

	Student& setName(std::string name);
	Student& setGender(char gender);
	Student& setAge(int age);
	Student& setScores(float score, int seq);
	Student& setScores(float scores[]);

	void print() const;
	void exportTo(FILE* fp) const;

	friend void obtain(FILE* fp, Database& database);
	friend std::ostream & operator << (std::ostream &os, const Student &rhs);

private:
	std::string name_ = "[NO NAME]";
	char gender_ = 'N';
	int age_ = 0;
	float score_[scoreNum] = {0};
};

void obtain(FILE* fp, Database& database);

#endif // STUDENT_H
