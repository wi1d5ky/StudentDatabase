#include "Database.h"
#include "Student.h"

#include <cstdlib>


Database::Database()
{
	_student = nullptr;
	_studentNum = 0;
}

Database& Database::Add(Student student)
{
	Student* tmp = _student;
	_student = (Student*) calloc(sizeof(Student), _studentNum + 1);
	bool inserIn = false;
	for(int i = 0; i < _studentNum ; ++i)
		if(student.Name().compare( tmp[i].Name() ) < 0 && !inserIn )
		{
			_student[i] = student;
			inserIn = true;
		}
		else
			_student[i] = tmp[i - (inserIn? 1:0)];

	_student[_studentNum] = inserIn? tmp[_studentNum - 1] : student;

	if(_studentNum > 0)
		free(tmp);

	++_studentNum;
	return *this;
}

Database& Database::operator << (Student student)
{
	Add(student);
	return *this;
}

const Database Database::recover(std::string name)
{
	Database database;
	for(int i = 0 ; i < _studentNum ; i++)
		if( name.compare(_student[i].Name()) == 0)
			database.Add(_student[i]);
	return database;
}
const Database Database::recover(Student student)
{
	return recover(student.Name());
}

Database& Database::Del(std::string name)
{
	for(int i = 0 ; i < _studentNum ; i++)
		if( name.compare(_student[i].Name()) == 0)
		{
			Student* tmp = _student;
			--_studentNum;
			_student = (Student*) calloc(sizeof(Student),_studentNum);
			for(int j = 0; j < i ; ++j)
				_student[j] = tmp[j];
			for(int j = i; j < _studentNum ; ++j)
				_student[j] = tmp[j+1];
			free(tmp);
			break;
		}
	return *this;
}

Database& Database::Del(Student student)
{
	Del(student.Name());
	return *this;
}

Database& Database::Drop()
{
	if(_studentNum != 0)
	{
		free(_student);
		_student = nullptr;
		_studentNum = 0;
	}
	return *this;
}

void Database::showAll() const
{
	if(_studentNum == 0)
	{
		std::cout << "<Empty>" << std::endl;
	}
	for(int i = 0; i < _studentNum ; ++i)
		std::cout << _student[i];
	std::cout << std::endl;
}

void Database::showAll()
{
	static_cast<const Database &>(*this).showAll();
}

void Database::exportTo(FILE* fp) const
{
	if(_studentNum == 0)
	{
		fprintf(fp, "<Empty>\n");
	}
	for(int i = 0; i < _studentNum ; ++i)
		_student[i].Print(fp);
}

void Database::importFrom(FILE* fp)
{
	if(_studentNum != 0)
	{
		free(_student);
		_student = nullptr;
		_studentNum = 0;
	}

	Student newStudent;

	char name[maxNameLength];
	char gender = 'N';
	int age = 0;

	while(fscanf(fp, "%s %c (%d) ", name, &gender, &age) != EOF)
	{
		newStudent.setName(name).setGender(gender).setAge(age);
		for(int i = 0 ; i< scoreNum ; ++i)
		{
			float score;
			fscanf(fp, " %f", &score);
			newStudent.setScores( score, i);
		}
		Add(newStudent);
	}
}

std::ostream & operator << (std::ostream &os, const Database &rhs)
{
	rhs.showAll();
	return os;
}
