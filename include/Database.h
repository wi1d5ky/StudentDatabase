#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>

constexpr int studentMaxNum = 100;
class Student;

class Database
{
public:

	const int studentNum()
	{
		return static_cast<const Database &>(*this).studentNum();
	};
	const int studentNum() const
	{
		return recordNum_;
	};
	Database& add(const Student& student);
	Database& operator << (const Student& student);
	const Database recover(std::string name) const;
	void print() const;
	void importFrom(FILE* fp);
	void exportTo(FILE* fp) const;
	friend std::ostream& operator << (std::ostream &os, const Database &rhs);

private:
	Student* table_ = nullptr;
	int recordNum_ = 0;
};

#endif // DATABASE_H
