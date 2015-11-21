#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

constexpr int scoreNum = 3;

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
	bool Print(FILE* fp);
	bool Print(FILE* fp) const;

	friend std::ostream & operator << (std::ostream &os, const Student &rhs);

private:
	std::string _name = "";
	char _gender = 'N';
	int _age = 0;
	float _score[scoreNum] = {0};
};

#endif // STUDENT_H
