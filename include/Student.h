#ifndef STUDENT_H
#define STUDENT_H

#include <string>

constexpr int scoreNum = 3;

class Student
{
public:
	Student();
	void setName(std::string name)
	{
		_name = name;
	};
	void setGender(char gender)
	{
		_gender = gender;
	};
	void setAge(int age)
	{
		_age = age;
	};
	void setScores(float score, int seq)
	{
		_score[seq] = score;
	};
	void setScores(float scores[])
	{
		for(int i = 0; i < scoreNum; ++i)
			_score[i] = scores[i];
	};
	void Print();
	const std::string Name()
	{
		return _name;
	};
	const std::string Name() const
	{
		return _name;
	};
private:
	std::string _name = "";
	char _gender = 'M';
	int _age = 0;
	float _score[scoreNum] = {0};
};

#endif // STUDENT_H
