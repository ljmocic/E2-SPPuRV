#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <algorithm>


//OBAVEZNO: podesiti argumente npr. baza_studenata.txt ime prezime
using namespace std;

// помоћне функције
static bool loadStudents(string fileName);
static void printStudentNames();
static void printStudentIndexNums();
static void printStudentNamesAndIndexNums();
static void addStudent();
static void makeIndexToNameMap();
static void printIndexToNameMap();
static void printDesiredIndex(int x);
static void makeNameToIndexMap();
static void printDesiredName(string name);
static void printSpecial();
static void replace();

// глобалне променљиве
static list<string> studentNames;
static vector<int> studentIndexNums;
static map<int, string> studentIndexToNameMap;
static map<string, int> studentNameToIndexMap;


int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Niste uneli potrebne argumente za pokretanje programa!" << endl;
		cout << "Argumenti komandne linije treba da budu:" << endl;
		cout << "1. apsolutna ili relativna putanja do datoteke: \"baza_studenata.txt\"" << endl;
		cout << "2. ime studenta" << endl;
		cout << "3. prezime studenta" << endl;
		exit(-1);
	}

	bool retVal;

	retVal = loadStudents(argv[1]);

	if (retVal == false)
	{
		cout << "Greska prilikom ucitavanja ulazne datoteke!\n" << endl;
		exit(-1);
	}

	printStudentNames();
	printStudentIndexNums();

	printStudentNamesAndIndexNums();

	addStudent();

	printStudentNamesAndIndexNums();

	makeIndexToNameMap();
	printIndexToNameMap();

	int x;
	cout << "Unesite broj indeksa: ";
	cin >> x;

	printDesiredIndex(x);

	makeNameToIndexMap();

	string name;
	string surname;
	// TODO: име и презиме студента преузети из прослеђених аргумената командне линије
	name = argv[2];
	surname = argv[3];

	string fullName;
	// TODO: формирај од имена и презимена један знаковни низ
	fullName = name + " " + surname;

	printDesiredName(fullName);

	// Додатни
	printSpecial();

	replace();

	cout << endl << endl;

	system("pause");

	return 0;
}


bool loadStudents(string fileName)
{
	// учитава датотеку "baza_studenata.txt"

	ifstream inputFile(fileName);

	if (inputFile.is_open() == false)
	{
		cout << endl << "GRESKA! Pogresno ime datoteke" << endl << endl;
		return false;
	}

	string ime;
	string prezime;
	int brojIndeksa;

	do
	{
		inputFile >> ime;
		inputFile >> prezime;
		inputFile >> brojIndeksa;

		// место за код
		// TODO: направите од имена и презимена један знаковни низ: надаље "име" се односи на име и презиме
		// TODO: попуните studentNames са именима, а studentIndexNums са бројевима индекса
		
		studentNames.push_back(ime + " " + prezime);
		studentIndexNums.push_back(brojIndeksa);


	} while (inputFile.eof() == false);

	inputFile.close();

	return true;
}


void printStudentNames()
{
	// TODO: имплементирати
	
	list<string>::iterator itNames = studentNames.begin();

	for(; itNames != studentNames.end() ; itNames++){
		cout<< *itNames << " " << endl;
	}
}


void printStudentIndexNums()
{
	// штампа на екран студентске индексе али у обрнутом редоследу
	// TODO: имплементирати
	vector<int>::reverse_iterator itIndex = studentIndexNums.rbegin();

	for(; itIndex != studentIndexNums.rend() ; itIndex++){
		cout<< *itIndex << endl;
	}
}


void printStudentNamesAndIndexNums()
{
	// штампа на екран име студента праћено бројем индекса

	// користити информације у studentNames и studentIndexNums
	// TODO: имплементирати

	list<string>::iterator itNames = studentNames.begin();
	vector<int>::iterator itIndex = studentIndexNums.begin();

	for(; itNames != studentNames.end() || itIndex != studentIndexNums.end() ; itNames++, itIndex++){
		cout<< *itNames << " " << *itIndex << endl;
	}
}


void addStudent()
{
	string studentsName = "Marko Kraljevic";
	int studentsIndexNum = 54321;

	list<string>::iterator itNames = studentNames.begin();
	vector<int>::iterator itIndex = studentIndexNums.begin();

	for(; itNames != studentNames.end() || itIndex != studentIndexNums.end(); itNames++, itIndex++){
		if(*itNames == "Mali Radojica" && *itIndex == 12345){
			break;
		}
	}

	studentNames.insert(itNames, studentsName);
	studentIndexNums.insert(itIndex, studentsIndexNum);

	// TODO: додати студента Краљевића Марка тачно иза Малог Радојице (12345)
}


void makeIndexToNameMap()
{
	// TODO: направити мапу пресликавања бројева индекса на имена
	list<string>::iterator itNames = studentNames.begin();
	vector<int>::iterator itIndex = studentIndexNums.begin();

	for(; itNames != studentNames.end() || itIndex != studentIndexNums.end() ; itNames++, itIndex++){
		studentIndexToNameMap[*itIndex] = *itNames;
	}


}


void printIndexToNameMap()
{
	map<int, string>::iterator itMap = studentIndexToNameMap.begin();
	for(; itMap != studentIndexToNameMap.end() || itMap != studentIndexToNameMap.end() ; itMap++ ){
		cout << itMap->first << " " << itMap->second << endl;
	}
}


void printDesiredIndex(int x)
{
	// TODO: наћи име студента у мапи на основу броја индекса, и одшампати име на екран
	// претпоставити да је број индекса увек валидан
	if( studentIndexToNameMap.find(x) != studentIndexToNameMap.end() ){
		cout<< studentIndexToNameMap[x] << endl;
	}
}


void makeNameToIndexMap()
{
	// TODO: направити мапу пресликавања имена на бројеве индекса
	list<string>::iterator itNames = studentNames.begin();
	vector<int>::iterator itIndex = studentIndexNums.begin();

	for(; itNames != studentNames.end() || itIndex != studentIndexNums.end() ; itNames++, itIndex++){
		studentNameToIndexMap[*itNames] = *itIndex;
	}
}


void printDesiredName(string name)
{
	// TODO: наћи индекс студента на основу имена, и одшампати индекс на екран
	// претпоставити да је могућ унос невалидног имена
	if( studentNameToIndexMap.find(name) != studentNameToIndexMap.end() ){
		cout<< studentNameToIndexMap[name] << endl;
	}
}


void printSpecial()
{
	// TODO: коришћењем итератора проћи кроз целу мапу studentIndexToNameMap
	// и исписати на екран парове индекс и име_презиме студената, за све студенте
	// осим последњег. За последњег студента исписати само име и презиме.
	map<int, string>::iterator itMap = studentIndexToNameMap.begin(), kraj = --studentIndexToNameMap.end();

	for(; itMap != kraj; itMap++){
		cout << itMap->first << " " << itMap->second << endl;
	}
	cout << itMap->second << endl;
}


void replace()
{
	// TODO: коришћењем метода знаковног низа у задатој реченици заменити зарезе размацима
	string str = "Sve,zareze,izmedju,reci,zameniti,razmacima";

	cout << endl << "Recenica koju treba prepraviti je:";
	cout << endl << str << endl;

	// TODO: имплементирати замену
	replace(str.begin(),str.end(), ',', ' '); 

	cout << endl << "Ispravljena recenica:";
	cout << endl << str << endl;
}
