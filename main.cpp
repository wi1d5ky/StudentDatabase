#include <iostream>
#include "Student.h"

using namespace std;

#define TEST_MODE 1


#if TEST_MODE == 1
int main()
{
	std::cout << "============= TEST Student =============" << endl << endl;
    Student* s = new Student();
	s->setName("Wildsky");
	s->setAge(20);
	s->setGender('M');
	for(int i = 0 ; i < scoreNum ; ++i)
		s->setScores( 99, i);
	s->Print();
}
#else
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
#endif // TEST_MODE
