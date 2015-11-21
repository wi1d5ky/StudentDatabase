#include <iostream>
#include "Student.h"
#include "Database.h"

using namespace std;

#define TEST_MODE 1

#if TEST_MODE == 1
int main()
{
	cout << "[=== TEST Student ===]" << endl << endl;
	Student s;
	s.setName("Wildsky").setAge(20);
	Student s2;
	s2.setName("Wlogsky").setAge(20);
	Student s3;
	s3.setName("Ryanooo").setAge(20);
	Student s4;
	s4.setName("Herbatnikiy").setAge(20).setGender('F');
	Student s5;
	s5.setName("WaitingFor19").setAge(20).setGender('F');

	for(int i = 0 ; i < scoreNum ; ++i)
		s.setScores( 100 - 2 * i, i);
	for(int i = 0 ; i < scoreNum ; ++i)
		s2.setScores( 100, i);
	for(int i = 0 ; i < scoreNum ; ++i)
		s3.setScores( 99, i);
	for(int i = 0 ; i < scoreNum ; ++i)
		s4.setScores( 98 , i);
	for(int i = 0 ; i < scoreNum ; ++i)
		s5.setScores( 97 , i);

	cout << "s  is "<< s;
	cout << "s2 is "<< s2;
	cout << "s3 is "<< s3;
	cout << "s4 is "<< s4;
	cout << "s5 is "<< s5;

	/** ================================================== **/

	cout << endl << "[=== TEST Database ===]" << endl << endl;
	Database d;
	cout << d;

	/* ----------------- */

	cout << endl << "[=== TEST Database = {Add} =]" << endl << endl;
	d << s2 << s3 << s4 << s << s5;
	cout << d;

	/* ----------------- */

	cout << endl << "[=== TEST Database = {Get} =]" << endl << endl;
	cout << *(d.get(s5));

	/* ----------------- */

	cout << endl << "[=== TEST Database = {Del} =]" << endl << endl;
	d.Del("Herbatnikiy");
	d.Del(s3);
	cout << d;

	/* ----------------- */

	cout << endl << "[=== TEST Database = {Drop} =]" << endl << endl;

	cout << d.Drop();

	return 0;
}
#else
int main()
{
	cout << "Hello world!" << endl;
	return 0;
}
#endif // TEST_MODE
