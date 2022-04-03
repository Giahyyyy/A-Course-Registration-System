#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#pragma warning(disable : 4996)

using namespace std;

struct Teacher
{
	string FirstName, Name, Sex, Email, Acc, Pass;
};

struct Date
{
	int day, month, year;
};

struct Mark
{
	string Total = "", Midterm = "", Final = "", Other = "";
};

struct Data
{
	string StudentID, FirstName, Name;
	int j, k;
	Data* pNext;
	Mark Score;
};

struct Course
{
	string NameOfCourse, CourseID, NameOfTeacher, NumOfCredit, Day1, Day2, Session1, Session2;
	Course* pNext;
	Data* DataOfStu = nullptr;//50 
	int NumOfStu = 0, MaxStu = 50;
	Mark Score;
};

struct Student
{
	int* Mark, NumOfOpt; //Mark la diem cac mon
	string Name, FirstName, StudentID, Pass, Sex, DOB, ID, Num; //StudentID la MSSV, ID la CCCD
	Course* Registered = nullptr;
};

struct Class
{
	string NameOfClass = "";
	Student* Stu;
	int NumOfStudent;
};

struct Semester
{
	Course* pCourse = nullptr;
	string StartSem;
	Date StartReg, EndReg, EndSem;;
};

struct Schoolyear
{
	Semester Sem[3];
	string NumOfYear = ""; // nam hoc
	Class* CLass;
	Schoolyear* YearNext;
	int NumOfClass;
};

void gotoxy(int x, int y);

void clear();

void InputAccount(string& name, string& Pass);

void AddYear(Schoolyear*& Ny);

void InputStaff(Teacher*& S, int& NumOfS);

int CheckLogin(string username, string Pass, Schoolyear*& Year, Teacher* S, int NumOfS);

void ViewIn(int x, Schoolyear* Year, Teacher* Staff);

void ChangePass(Schoolyear* Year, Teacher* Staff, int x, int NumOfStaff);///

void AddSem(Schoolyear*& Year, int& x);

void AddCou(Course*& Cou);

void ViewCou(Course* Cou, int& t, int& i);//

void UpdateCou(Schoolyear* Year, int Se);

void SaveInfoCou(Schoolyear* Year, int Se);

void DeleteCou(Schoolyear*& Year, int Se);

void Now(Date& Today);

bool CheckDateRegister(Date Today, Date StartReg, Date EndReg);

bool CheckDateEndSemester(Date Today, Date EndSem);

bool CheckImport(Schoolyear* YearCur, int x);

void CourseEnroll(Schoolyear* YearCur, Course* CourseHead, int x, int& NumOfOpt);

void ViewListEnrolled(Schoolyear* YearCur, int x);

void RemoveCourseEnrolled(Schoolyear* YearCur, Course* CourseHead, int x);

void ViewListClasses(Schoolyear* YearCur);

void ViewListStudentInClass(Schoolyear* YearCur);

void ViewListStudentInCourse(Schoolyear* YearCur, int sem);

void ExportListStudentCourse(Course* CourseHead);

void LoadScoreboard(Course*& CourseHead, Schoolyear*& YearCur);

void ViewScoreboardCourse(Course* CourseHead);

void ViewScoreboardClass(Schoolyear* YearCur, int x);

void ViewScoreboardStu(Schoolyear* YearCur, int x);

void UpdateStudentResult(Schoolyear*& YearCur, Course*& CourseHead);

