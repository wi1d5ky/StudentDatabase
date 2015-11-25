#include "Database.h"
#include "Student.h"
#include <cstdio>

Database& Database::add(const Student& student)
{
	Student* previous = table_;
	bool inserted = false;

	table_ = new Student[recordNum_+1];

	for(int i = 0; i < recordNum_ ; ++i)
		if(!inserted && student.Name().compare( previous[i].Name() ) < 0 )
		{
			table_[i] = student;
			inserted = true;
		}
		else
			table_[i] = previous[i - (inserted? 1:0)];	// if added, offset

	table_[recordNum_] = inserted? previous[recordNum_ - 1] : student;

	if(recordNum_ > 0)
		delete previous;

	++recordNum_;
	return *this;
}

Database& Database::operator << (const Student& student)
{
	return add(student);
}

const Database Database::recover(std::string name) const
{
	Database result;
	for(int i = 0 ; i < recordNum_ ; i++)
		if( name.compare(table_[i].Name()) == 0)
			result.add(table_[i]);
	return result;
}

void Database::print() const
{
	exportTo(stdout);
}

void Database::exportTo(FILE* fp) const
{
	if(fp == nullptr)
	{
		std::cout << "Export Failed." << std::endl;
		return;
	}
	if(recordNum_ == 0)
		fprintf(fp, "<Empty>\n");
	for(int i = 0; i < recordNum_ ; ++i)
		table_[i].exportTo(fp);
	fprintf(fp, "\n");
}

void Database::importFrom(FILE* fp)
{
	if(fp == nullptr)
	{
		std::cout << "Import Failed." << std::endl;
		return;
	}

	// Drop table_
	if(recordNum_ != 0)
	{
		delete table_;
		table_ = nullptr;
		recordNum_ = 0;
	}

	obtain(fp, *this);
}

std::ostream & operator << (std::ostream &os, const Database &rhs)
{
	rhs.print();
	return os;
}
