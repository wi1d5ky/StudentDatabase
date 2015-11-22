#include <iostream>
#include <cstdlib>
#include "Student.h"
#include "Database.h"

using namespace std;

constexpr int featureNum = 6; // incl. exit

inline void pause() {
    printf("Press Enter key to continue...");
    getchar();
}

inline void clean() {
    #ifdef _WIN32
	system("cls");
	#endif

	#ifdef __linux__
	system("clear");
	#endif
}

int showMenu();
void addRecordTo(Database& database);
void searchIn(Database database);
void exportFrom(const Database database);
void importAs(Database& database);

int main()
{
	Database database;

	while(1)
	{
		switch(showMenu())
		{
		case 1:
			addRecordTo(database);
			break;
		case 2:
			cout << "There are " << database.studentNum() << " records:" << endl << endl;
			cout << database;
			break;
		case 3:
			searchIn(database);
			break;
		case 4:
			exportFrom(database);
			break;
		case 5:
			importAs(database);
			break;
		case 6:
			cout << endl << "BYE!" << endl ;
			return 0;
		default:
			cout << "ERROR! Please input 1 ~ " << featureNum << "." << endl << endl;
			break;
		}
		pause();
	}
	return 0;
}

int showMenu()
{
	clean();
	string functions[] =
	{
		"Add a record",
		"Show all records",
		"Search student(s) by name",
		"Output records to a text file",
		"Input records from a text file",
		"Exit the program"
	};

	cout << "A simple database program" << endl << endl;
	for(int i = 0; i < featureNum ; ++i)
		cout << "(" << i+1 << ") " << functions[i] << endl << endl;

	cout << "Please select a function...>";
	int choice = 0;
	cin >> choice;
	getchar();	// Eat the enter

	clean();

	return choice;
}

void addRecordTo(Database& database)
{
	Student newborn;
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
	getchar();

	database << newborn.setName(name).setGender(gender).setAge(age).setScores(scores);

	cout << endl << "Done!" << endl << endl;
}

void searchIn(Database database)
{
	cout << "Please input the name of the student...>";
	char name[maxNameLength];
	cin >> name;
	getchar();
	cout << endl;

	const Database searchResult = database.recover(name);

	if(searchResult.studentNum())
	{
		cout << "There is/are " << searchResult.studentNum() << " \"" << name << "\":" << endl << endl;
		cout << searchResult;
	}
	else
		cout << "There is no \"" << name << "\"." << endl << endl;
}

void exportFrom(const Database database)
{
	cout << "Output all records to a text file." << endl << endl;
	cout << "Note that the original data in the file will be lost after writing to the file. Are you sure that you want to continue? (y/N)...>";

	char confirm = getchar();
	if(confirm != '\n')
		getchar();
	if (confirm == 'y' || confirm == 'Y')
	{
		string filename;
		cout << endl << "Please input the name of the file...>";
		cin >> filename;
		getchar();
		cout << endl << "Data will be exported to " << filename << " ..." << endl << endl;

		FILE* fp = fopen(filename.c_str(), "w");
		if(fp != nullptr)
		{
			database.exportTo(fp);
			fclose(fp);
			cout << "Done." << endl << endl;
		}
		else
			cout << "Export ERROR." << endl << endl;
	}
	else
		cout << endl << "Export aborted." << endl << endl;
}

void importAs(Database& database)
{
	cout << "Read in records from a text file." << endl << endl;
	cout << "Note that current data in the program will be lost after reading. Are you sure that you want to continue? (y/N)...>";

	char confirm = getchar();
	if(confirm != '\n')
		getchar();
	if (confirm == 'y' || confirm == 'Y')
	{
		string filename;
		cout << endl << "Please input the name of the file...>";
		cin >> filename;
		getchar();
		cout << endl;

		FILE* fp = fopen(filename.c_str(), "r");
		database.importFrom(fp);
		fclose(fp);
	}
	else
		cout << endl << "Import aborted." << endl << endl;
}
