#include "Database.h"
#include "Student.h"

Database::Database()
{
	_table = nullptr;
	_recordNum = 0;
}

Database& Database::add(const Student student)
{
	Student* previous = _table;
	bool inserIn = false;

	_table = (Student*) calloc(sizeof(Student), _recordNum + 1);

	for(int i = 0; i < _recordNum ; ++i)
		if(!inserIn && student.Name().compare( previous[i].Name() ) < 0 )
		{
			_table[i] = student;
			inserIn = true;
		}
		else
			_table[i] = previous[i - (inserIn? 1:0)];	// if added, offset

	_table[_recordNum] = inserIn? previous[_recordNum - 1] : student;

	if(_recordNum > 0)
		free(previous);

	++_recordNum;
	return *this;
}

Database& Database::operator << (const Student student)
{
	return add(student);
}

const Database Database::recover(std::string name) const
{
	Database result;
	for(int i = 0 ; i < _recordNum ; i++)
		if( name.compare(_table[i].Name()) == 0)
			result.add(_table[i]);
	return result;
}

void Database::print() const
{
	exportTo(stdout);
}

void Database::print()
{
	static_cast<const Database &>(*this).print();
}

void Database::exportTo(FILE* fp) const
{
	if(fp == nullptr)
	{
		std::cout << "Export Failed." << std::endl;
		return;
	}
	if(_recordNum == 0)
		fprintf(fp, "<Empty>\n");
	for(int i = 0; i < _recordNum ; ++i)
		_table[i].Print(fp);
	fprintf(fp, "\n");
}

void Database::importFrom(FILE* fp)
{
	if(fp == nullptr)
	{
		std::cout << "Import Failed." << std::endl;
		return;
	}
	drop();
	obtain(fp, *this);
}

std::ostream & operator << (std::ostream &os, const Database &rhs)
{
	rhs.print();
	return os;
}

Database& Database::del(const std::string name)
{
	for(int i = 0 ; i < _recordNum ; i++)
		if( _table[i].Name().compare(name) == 0 )
		{
			Student* previous = _table;
			--_recordNum;
			_table = (Student*) calloc(sizeof(Student), _recordNum);
			for(int j = 0; j < _recordNum ; ++j)
				_table[j] = previous[j + (j < i ? 0 : 1 )];
			free(previous);
		}
	return *this;
}

Database& Database::drop()
{
	if(_recordNum != 0)
	{
		free(_table);
		_table = nullptr;
		_recordNum = 0;
	}
	return *this;
}
