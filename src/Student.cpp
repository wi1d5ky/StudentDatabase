#include "Student.h"
#include <iostream>

Student::Student()
{

}

void Student::Print()
{
	std::cout<< _name << " " << _gender << " (" << _age << ")";
	for(int i = 0; i < scoreNum ; ++i)
	{
		std::cout << " " << _score[i];
	}
	std::cout << std::endl;
}

