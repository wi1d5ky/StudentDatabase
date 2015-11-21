#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>

class Student;
constexpr int studentMaxNum = 100;

class Database
{
public:
	Database& Add(Student& student);
	Database& operator << (Student student);
	Student* get(std::string name);
	Student* get(Student student);
	Database& Del(std::string name);
	Database& Del(Student student);
	Database& Drop();
	void showAll();
	void showAll() const;
	void exportTo(FILE* fp);
	friend std::ostream & operator << (std::ostream &os, const Database &rhs);
private:
	Student* _student;
	int _studentNum = 0;
};

#endif // DATABASE_H
