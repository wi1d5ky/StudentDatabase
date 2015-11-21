#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>

class Student;
constexpr int studentMaxNum = 100;

class Database
{
public:
	Database();
	const int studentNum()
	{
		return static_cast<const Database &>(*this).studentNum();
	};
	const int studentNum() const
	{
		return _studentNum;
	};
	Database& Add(Student student);
	Database& operator << (Student student);
	const Database recover(std::string name);
	const Database recover(Student student);
	Database& Del(std::string name);
	Database& Del(Student student);
	Database& Drop();
	void showAll();
	void showAll() const;
	void exportTo(FILE* fp) const;
	void importFrom(FILE* fp);
	friend std::ostream & operator << (std::ostream &os, const Database &rhs);
private:
	Student* _student;
	int _studentNum = 0;
};

#endif // DATABASE_H
