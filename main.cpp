#include <iostream>
#include "Student.h"
#include "Database.h"

constexpr int functionNum = 6; // incl. exit

using namespace std;

void showMenu();
void addRecord(Database& database);
void searchStudent(Database database);
void exportToFile(const Database database);
void readDataFromFile(Database& database);

#define TEST_MODE 0

#if TEST_MODE == 1
int main()
{
	FILE* fp;

	cout << "[=== TEST Student ===]" << endl << endl;
	Student s;
	s.setName("Wildsky").setAge(20).setGender('M');
	Student s2;
	s2.setName("Wlogsky").setAge(20).setGender('M');
	Student s3;
	s3.setName("Ryanooo").setAge(20).setGender('M');
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
		s4.setScores( 98.5 , i);
	for(int i = 0 ; i < scoreNum ; ++i)
		s5.setScores( 97.9 , i);

	cout << "s  is "<< s;
	cout << "s2 is "<< s2;
	cout << "s3 is "<< s3;
	cout << "s4 is "<< s4;
	cout << "s5 is "<< s5;

	// ==================================================

	cout << endl << "[=== TEST Database ===]" << endl << endl;
	Database d;
	cout << d;

	// -----------------

	cout << endl << "[=== TEST Database = {Add} =]" << endl << endl;
	d << s2 << s3 << s4 << s << s5;
	cout << d;

	cout << endl << "[=== TEST Database = {Ept} =]" << endl << endl;
	fp = fopen("export.txt", "w");
	d.exportTo(fp);
	fclose(fp);

	cout << endl << "[=== TEST Database = {Ipt} =]" << endl << endl;
	fp = fopen("export.txt", "r");
	d.importFrom(fp);
	fclose(fp);
	cout << d;

	// -----------------

	cout << endl << "[=== TEST Database = {Get} =]" << endl << endl;
	cout << d.recover(s5);

	// -----------------

	cout << endl << "[=== TEST Database = {Del} =]" << endl << endl;
	d.Del("Herbatnikiy");
	d.Del(s3);
	cout << d;
	// -----------------

	cout << endl << "[=== TEST Database = {Drop} =]" << endl << endl;

	cout << d.Drop();

	return 0;
}
#else
int main()
{
    cout << "A simple database program" << endl << endl;
	showMenu();

	int selectFunction = 0;

	Database database;

	cin >> selectFunction;

	while(1)
	{
		for(int i = 0 ; i < 3 ; ++i)
			cout << endl;
		cout << "==============";
		for(int i = 0 ; i < 3 ; ++i)
			cout << endl;

		switch(selectFunction)
		{
			case 1:
				addRecord(database);
				break;
			case 2:
				cout << "There are " << database.studentNum() << " records:" << endl << endl;
				database.showAll();
				break;
			case 3:
				searchStudent(database);
				break;
			case 4:
				exportToFile(database);
				break;
			case 5:
				readDataFromFile(database);
				break;
			case 6:
				cout << endl << "BYE!" << endl ;
				return 0;
			default:
				cout << "ERROR! Please input 1 ~ 6." << endl << endl;
				break;

		}

		selectFunction = 0;
		showMenu();
		cin >> selectFunction;
	}

	return 0;
}
#endif // TEST_MODE

void showMenu()
{
	string functions[] = {
		"Add a record",
		"Show all records",
		"Search student(s) by name",
		"Output records to a text file",
		"Input records from a text file",
		"Exit the program"
    };

    for(int i = 0; i < functionNum ; ++i)
		cout << "(" << i+1 << ") " << functions[i] << endl;
	cout << endl << "Please select a function...>";
}

void addRecord(Database& database)
{
	Student newStudent;
	char name[maxNameLength];
	char gender = 'N';
	int age = 0;
	float scores[scoreNum];

	cout << "Please input the required values:" << endl << endl;
	cout << "Name(No space): ";
	cin >> name;
	cout << "Gender(M/F): ";
	cin >> gender;
	cout << "Age: ";
	cin >> age;
	cout << scoreNum << " Scores: ";
	for(int i = 0 ; i< scoreNum ; ++i)
		cin >> scores[i];

	newStudent.setName(name).setGender(gender).setAge(age).setScores(scores);

	database.Add(newStudent);

	cout << "Done!" << endl;
}


void searchStudent(Database database)
{
    cout << "Please input the name of the student...>";
    char name[maxNameLength];
    cin >> name;
    cout << endl;

    const Database searchResult = database.recover(name);

	if(searchResult.studentNum() > 0)
	{
		cout << "There is/are " << searchResult.studentNum() << " \"" << name << "\":" << endl << endl;
		cout << searchResult;
	}
	else
		cout << "There is no \"" << name << "\"." << endl << endl;

}

void exportToFile(const Database database)
{
	getchar();
	cout << "Output all records to a text file." << endl << endl;
	cout << "Note that the original data in the file will be lost after writing to the file. Are you sure that you want to continue? (y/N)...>";

	char confirm = getchar();
	if (confirm == 'y' || confirm == 'Y')
	{
		string filename;
		cout << endl << "Please input the name of the file...>";
		cin >> filename;

		cout << endl;

		FILE* fp = fopen(filename.c_str(), "w");
		database.exportTo(fp);
		fclose(fp);
	}
	else
		cout << "Export aborted." << endl << endl;
}

void readDataFromFile(Database& database)
{
	getchar();
	cout << "Read in records from a text file." << endl << endl;
	cout << "Note that current data in the program will be lost after reading. Are you sure that you want to continue? (y/N)...>";

	char confirm = getchar();
	if (confirm == 'y' || confirm == 'Y')
	{
		string filename;
		cout << endl << "Please input the name of the file...>";
		cin >> filename;

		cout << endl;

		FILE* fp = fopen(filename.c_str(), "r");
		database.importFrom(fp);
		fclose(fp);
	}
	else
		cout << "Import aborted." << endl << endl;
}
