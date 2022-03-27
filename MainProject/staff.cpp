#include "staff.h"
#include <string>
using namespace std;

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void clear()
{
	for (int i = 0; i < 118; ++i) {
		for (int j = 3; j < 39; ++j)
		{
			gotoxy(i, j);
			cout << char(32);
		}
	}
	cout << endl;
}

void InputYourAcc(string& username, string& Pass)
{
	cout << "Input your username: ";
	getline(cin, username);
	cout << "Input your Pass: ";
	getline(cin, Pass);
	cout << endl;
}

void AddNewYear(Schoolyear*& NewYear) // Khi tham chieu thi tham chieu YearNow->YearNext sau khi het ham thi cho YearNow=YearNow->YearNext
{
	if (!NewYear) NewYear = new Schoolyear;
	cout << "Input school year: ";
	cin >> NewYear->NumOfYear;
	cout << endl;
	cout << "Input number of classes: ";
	cin >> NewYear->NumOfClass;
	cin.ignore();
	NewYear->CLass = new Class[NewYear->NumOfClass];
	for (int i = 0; i < NewYear->NumOfClass; i++)
	{
		while (true)
		{
			cout << "Input name of the class: ";
			getline(cin, NewYear->CLass[i].NameOfClass);
			ifstream in(NewYear->CLass[i].NameOfClass + ".csv");
			if (in.is_open()) break;
			else
			{
				cout << "Can not open files to input data!!!";
			}
		}
		string temp;
		ifstream in(NewYear->CLass[i].NameOfClass + ".csv");
		getline(in, temp, ',');
		NewYear->CLass[i].NumOfStudent = stoi(temp);
		NewYear->CLass[i].Stu = new Student[stoi(temp)];
		getline(in, temp);
		for (int j = 0; j < NewYear->CLass[i].NumOfStudent; j++)
		{
			getline(in, NewYear->CLass[i].Stu[j].Num, ',');
			getline(in, NewYear->CLass[i].Stu[j].StudentID, ',');
			getline(in, NewYear->CLass[i].Stu[j].FirstName, ',');
			getline(in, NewYear->CLass[i].Stu[j].Name, ',');
			getline(in, NewYear->CLass[i].Stu[j].Sex, ',');
			getline(in, NewYear->CLass[i].Stu[j].DOB, ',');
			getline(in, NewYear->CLass[i].Stu[j].ID, ',');
			getline(in, NewYear->CLass[i].Stu[j].Pass);
			NewYear->CLass[i].Stu[j].Registered = nullptr;
		}
		cout << "Input data of class " << NewYear->CLass[i].NameOfClass << " successfully" << endl;
	}
	NewYear->YearNext = nullptr;
}

int CheckLogin(string username, string Pass, Schoolyear*& YearCur, Teacher* Staff, int NumOfStaff)
{
	if (username[0] >= 'a' && username[0] <= 'z')
	{
		int i = 0;
		for (i; i < NumOfStaff; i++)
		{
			if (username == Staff[i].Acc && Pass == Staff[i].Pass)
				return i + 1;
		}
		return 0;
	}
	else if (username[0] >= 'A' && username[0] <= 'Z')
		return 0; //Vì username mình cấp không có chữ in hoa
	else if (username[0] >= 48 && username[0] <= 57 && username.length() == 8)
	{
		if (username[1] >= 48 && username[1] <= 57)
		{
			int x = ((int)username[0] - 48) * 10 + (int)username[1] - 48;
			while (YearCur != nullptr && x != ((((int)YearCur->NumOfYear[2]) - 48) * 10 + ((int)YearCur->NumOfYear[3] - 48)))
				YearCur = YearCur->YearNext;
			if (YearCur == nullptr) return 0;
			else
			{
				for (int i = 0; i < YearCur->NumOfClass; i++)
					for (int j = 0; j < YearCur->CLass[i].NumOfStudent; j++)
						if (username == YearCur->CLass[i].Stu[j].StudentID && YearCur->CLass[i].Stu[j].Pass == Pass)
							return (i + 1) * 100 + j + 1;
				return 0;
			}
		}
		else return 0;
	}
	else return 0;
}

void InputStaff(Teacher*& Staff, int& NumOfStaff)
{
	ifstream in("StaffAcc.csv");
	string temp;
	getline(in, temp, ',');
	NumOfStaff = stoi(temp);
	Staff = new Teacher[stoi(temp)];
	getline(in, temp);
	for (int i = 0; i < NumOfStaff; i++)
	{
		getline(in, Staff[i].FirstName, ',');
		getline(in, Staff[i].Name, ',');
		getline(in, Staff[i].Sex, ',');
		getline(in, Staff[i].Email, ',');
		getline(in, Staff[i].Acc, ',');
		getline(in, Staff[i].Pass);
	}

}

void ViewInfo(int x, Schoolyear* YearCur, Teacher* Staff)
{
	if (x < 100)
	{
		cout << "Fullname: " << Staff[x - 1].FirstName << " " << Staff[x - 1].Name << endl;
		cout << "Sex: " << Staff[x - 1].Sex << endl;
		cout << "Email: " << Staff[x - 1].Email << endl;
	}
	else
	{
		cout << "Fullname: " << YearCur->CLass[x / 100 - 1].Stu[x % 100 - 1].FirstName << YearCur->CLass[x / 100 - 1].Stu[x % 100 - 1].Name << endl;
		cout << "Class: " << YearCur->CLass[x / 100 - 1].NameOfClass << endl;
		cout << "Student ID: " << YearCur->CLass[x / 100 - 1].Stu[x % 100 - 1].StudentID << endl;
		cout << "Date of Birth: " << YearCur->CLass[x / 100 - 1].Stu[x % 100 - 1].DOB << endl;
		cout << "Sex: " << YearCur->CLass[x / 100 - 1].Stu[x % 100 - 1].Sex << endl;
		cout << "Social ID: " << YearCur->CLass[x / 100 - 1].Stu[x % 100 - 1].ID << endl;
		cout << "Pass" << YearCur->CLass[x / 100 - 1].Stu[x % 100 - 1].Pass << endl;
	}
}

void ChangePass(Schoolyear* YearCur, Teacher* Staff, int x, int NumOfStaff)
{
	string Pass;
	while (true)
	{
		cout << "Enter your new Pass: ";
		cin >> Pass;
		cin.ignore();
		cout << "Reenter your new Pass: ";
		string temp;
		getline(cin, temp);
		if (temp != Pass)
		{
			cout << "Input error. Please input again your new Pass!!!" << endl;
			Pass = "";
		}
		else break;
	}
	if (x < 100) Staff[x - 1].Pass = Pass;
	else YearCur->CLass[x / 100 - 1].Stu[x % 100 - 1].Pass = Pass;
	if (x < 100)
	{
		ofstream out("StaffAcc.csv", ios::trunc);
		out << NumOfStaff << ",,,,," << endl;
		for (int i = 0; i < NumOfStaff; i++)
		{
			out << Staff[i].FirstName << "," << Staff[i].Name << "," << Staff[i].Sex << "," << Staff[i].Email << "," << Staff[i].Acc << "," << Staff[i].Pass << endl;
		}
	}
	else
	{
		ofstream out(YearCur->CLass[x / 100 - 1].NameOfClass + ".csv", ios::trunc);
		out << YearCur->CLass[x / 100 - 1].NumOfStudent << ",,,,,,," << endl;
		for (int i = 0; i < YearCur->CLass[x / 100 - 1].NumOfStudent; i++)
		{
			out << YearCur->CLass[x / 100 - 1].Stu[i].Num << "," << YearCur->CLass[x / 100 - 1].Stu[i].StudentID << "," << YearCur->CLass[x / 100 - 1].Stu[i].FirstName << ","
				<< YearCur->CLass[x / 100 - 1].Stu[i].Name << "," << YearCur->CLass[x / 100 - 1].Stu[i].Sex << "," << YearCur->CLass[x / 100 - 1].Stu[i].DOB << ","
				<< YearCur->CLass[x / 100 - 1].Stu[i].ID << "," << YearCur->CLass[x / 100 - 1].Stu[i].Pass << endl;
		}
	}
	cout << "Your Pass was changed successfully." << endl;
}

void AddNewSemester(Schoolyear*& YearCur, int& x)
{
	string temp;
	cout << "Input school year: ";
	cin >> temp;
	cout << endl;
	while (YearCur && temp != YearCur->NumOfYear)
	{
		YearCur = YearCur->YearNext;
	}
	if (!YearCur)
	{
		cout << "This year is not valid." << endl;
		return;
	}
	cout << "Input semester: ";
	cin >> x;
	cin.ignore();
	x = x - 1;
	cout << "The dates have form dd/mm/yyyy." << endl;
	cout << "Input start date of this semester: ";
	getline(cin, YearCur->Sem[x].StartSem);
	cout << endl;
	cout << "Input end date of this semester: ";
	getline(cin, temp);
	cout << endl;
	YearCur->Sem[x].EndSem.day = (int)temp[0] * 10 + (int)temp[1] - 528;
	YearCur->Sem[x].EndSem.month = (int)temp[3] * 10 + (int)temp[4] - 528;
	YearCur->Sem[x].EndSem.year = (int)temp[6] * 1000 + (int)temp[7] * 100 + (int)temp[8] * 10 + (int)temp[9] - 53328;
	cout << "Input the date start to register course: ";
	getline(cin, temp);
	cout << endl;
	YearCur->Sem[x].StartReg.day = (int)temp[0] * 10 + (int)temp[1] - 528;
	YearCur->Sem[x].StartReg.month = (int)temp[3] * 10 + (int)temp[4] - 528;
	YearCur->Sem[x].StartReg.year = (int)temp[6] * 1000 + (int)temp[7] * 100 + (int)temp[8] * 10 + (int)temp[9] - 53328;
	cout << "Input the date end to register course: ";
	getline(cin, temp);
	cout << endl;
	YearCur->Sem[x].EndReg.day = (int)temp[0] * 10 + (int)temp[1] - 528;
	YearCur->Sem[x].EndReg.month = (int)temp[3] * 10 + (int)temp[4] - 528;
	YearCur->Sem[x].EndReg.year = (int)temp[6] * 1000 + (int)temp[7] * 100 + (int)temp[8] * 10 + (int)temp[9] - 53328;
	ifstream in(YearCur->NumOfYear + "_" + to_string(x + 1) + ".csv");
	if (!in.is_open())
	{
		cout << "Input fail.";
	}
	else
	{
		Course* Cur = nullptr;
		while (!in.eof())
		{
			if (!YearCur->Sem[x].pCourse)
			{
				YearCur->Sem[x].pCourse = new Course;
				Cur = YearCur->Sem[x].pCourse;
			}
			else
			{
				Cur->pNext = new Course;
				Cur = Cur->pNext;
			}
			getline(in, Cur->CourseID, ',');
			getline(in, Cur->NameOfCourse, ',');
			getline(in, Cur->NameOfTeacher, ',');
			getline(in, Cur->NumOfCredit, ',');
			getline(in, Cur->Day1, ',');
			getline(in, Cur->Session1, ',');
			getline(in, Cur->Day2, ',');
			getline(in, Cur->Session2);
			Cur->NumOfStu = 0;
			Cur->pNext = nullptr;
		}
		cout << "Input successfully.";
	}
}

void AddNewCourse(Course*& CourseHead)
{
	Course* temp = new Course;
	temp->NumOfStu = 0;
	cout << "Input course ID: ";
	getline(cin, temp->CourseID);
	cout << "Input name of course: ";
	getline(cin, temp->NameOfCourse);
	cout << "Input teacher name: ";
	getline(cin, temp->NameOfTeacher);
	cout << "Input number of credits: ";
	getline(cin, temp->NumOfCredit);
	cout << "Input day 1: ";
	getline(cin, temp->Day1);
	cout << "Input session 1: ";
	getline(cin, temp->Session1);
	cout << "Input day 2: ";
	getline(cin, temp->Day2);
	cout << "Input session 2: ";
	getline(cin, temp->Session2);
	temp->pNext = CourseHead;
	CourseHead = temp;
	cout << "Add new course successfully";
}

void ViewCourse(Course* CourseHead, int& t, int& i)
{
	clear();
	int k = 1;
	int y = 16, a = 20;
	Course* Cur = CourseHead;
	cout << endl;
	gotoxy(8, 15);
	cout << "Course ID";
	gotoxy(a, 15);
	a = a + 30;
	cout << "Name of course";
	gotoxy(a, 15);
	a = a + 10;
	cout << "Teacher";
	gotoxy(a, 15);
	a = a + 10;
	cout << "Credits";
	gotoxy(a, 15);
	a = a + 22;
	cout << "Number of Students";
	gotoxy(a, 15);
	cout << "Session";
	while (Cur)
	{
		int x = 20;
		gotoxy(6, y);
		cout << k;
		gotoxy(8, y);
		cout << Cur->CourseID;
		gotoxy(x, y);
		x = x + 30;
		cout << Cur->NameOfCourse;
		gotoxy(x, y);
		x = x + 13;
		cout << Cur->NameOfTeacher;
		gotoxy(x, y);
		x = x + 14;
		cout << Cur->NumOfCredit;
		gotoxy(x, y);
		x = x + 15;
		cout << Cur->NumOfStu << "/" << 50;
		gotoxy(x, y);
		cout << "Thu " << Cur->Day1 << " Ca " << Cur->Session1 << " Thu " << Cur->Day2 << " Ca " << Cur->Session2;
		y = y + 1;
		Cur = Cur->pNext;
		k++;
		cout << endl;
	}
	t = y;
	i = k;
}

void UpdateCourse(Schoolyear* YearCur, int sem)
{
	Course* Cur = YearCur->Sem[sem].pCourse;
	int count = 1, t, option;
	ViewCourse(YearCur->Sem[sem].pCourse, t, count);
	t++;
	cout << "Enter the course you want to update:";
	cin >> option;
	cin.ignore();
	Cur = YearCur->Sem[sem].pCourse;
	for (int i = 1; i < option; i++)
	{
		Cur = Cur->pNext;
	}
	cout << "You are choosing:" << Cur->NameOfCourse;
	cout << "1. Name of Teacher. ";
	cout << "2. Number of Credits. ";
	cout << "3. Present students enrolled. ";
	cout << "4. Day 1. ";
	cout << "5. Session 1. ";
	cout << "6. Day 2. ";
	cout << "7. Session 2. ";
	cout << "Enter your option: ";
	cin >> option;
	cin.ignore();
	switch (option)
	{
	case 1:
		cout << "Change the name of teacher: ";
		getline(cin, Cur->NameOfTeacher);
		break;
	case 2:
		cout << "Change the number of credits: ";
		getline(cin, Cur->NumOfCredit);
		break;
	case 3:
		cout << "Change the student enrolled: ";
		cin >> Cur->NumOfStu;
		break;
	case 4:
		cout << "Change the day 1: ";
		getline(cin, Cur->Day1);
		break;
	case 5:
		cout << "Change the session 1: ";
		getline(cin, Cur->Session1);
		break;
	case 6:
		cout << "Change the day 2: ";
		getline(cin, Cur->Day2);
		break;
	case 7:
		cout << "Change the session 2: ";
		getline(cin, Cur->Session2);
		break;
	default:
		break;
	}
	cout << "Update course successfully";
}

void SaveInfoCourse(Schoolyear* YearCur, int sem)
{
	Course* Cur = YearCur->Sem[sem].pCourse;
	ofstream course;
	course.open(YearCur->NumOfYear + "_" + (char)(sem + 49) + ".csv", ios::trunc);
	while (Cur != nullptr)
	{
		course << Cur->NameOfTeacher << "," << Cur->NumOfCredit << "," << Cur->NumOfStu << "," << Cur->Day1 << "," << Cur->Session1 << "," << Cur->Day2 << "," << Cur->Session2 << "\n";
		Cur = Cur->pNext;
	}
	course.close();
}

void DeleteCourse(Schoolyear*& YearCur, int sem)
{
	Course* Cur = YearCur->Sem[sem].pCourse;
	int count = 1, t, option;
	ViewCourse(YearCur->Sem[sem].pCourse, t, count);
	t++;
	cout << "Enter the course you want to update:";
	cin >> option;
	cin.ignore();
	Cur = YearCur->Sem[sem].pCourse;
	if (option <= count)
	{
		if (option == 1)
		{
			YearCur->Sem[sem].pCourse = YearCur->Sem[sem].pCourse->pNext;
			delete Cur;
		}
		else
		{
			for (int i = 2; i < option; i++)
			{
				Cur = Cur->pNext;
			}

			Course* temp = Cur->pNext;
			Cur->pNext = Cur->pNext->pNext;
			delete temp;
			cout << "Delete course successfully.";
			//SaveInfoCourse(YearCur, sem); //Goi lai ham Save de luu thong tin vao file csv
		}
	}
	else
	{
		cout << "This course is not existed!";
	}
}

void Now(Date& Today)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	Today.year = 1900 + ltm->tm_year;
	Today.month = 1 + ltm->tm_mon;
	Today.day = ltm->tm_mday;
}

bool CheckDateRegister(Date Today, Date StartReg, Date EndReg)
{
	if (Today.year >= StartReg.year && Today.year <= EndReg.year) {
		if (Today.month >= StartReg.month && Today.month <= EndReg.month) {
			if (Today.day >= StartReg.day && Today.day <= EndReg.day) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool CheckDateEndSemester(Date Today, Date EndSem)
{
	if (Today.year > EndSem.year)
		return true;
	else if (Today.year == EndSem.year)
	{
		if (Today.month > EndSem.month)
			return true;
		else if (Today.month == EndSem.month)
			if (Today.day > EndSem.day)
				return true;
	}
	return false;
}

bool CheckImport(Schoolyear* YearCur, int x)
{
	if (!YearCur->CLass[x / 100 - 1].Stu[x % 100 - 1].Registered) return false;
	if (YearCur->CLass[x / 100 - 1].Stu[x % 100 - 1].Registered->Score.Final == "") return false;
	return true;
}

void CourseEnroll(Schoolyear* YearCur, Course* CourseHead, int x, int& NumOfOpt)
{
	int opt;
	int j = (x / 100) - 1;
	int k = (x % 100) - 1;
	Course* ListEnroll = YearCur->CLass[j].Stu[k].Registered;
	while (ListEnroll != nullptr && ListEnroll->pNext != nullptr)
	{
		ListEnroll = ListEnroll->pNext;
	}
	while (NumOfOpt != 5)
	{
	Enroll:
		Data* InfoCur = nullptr;
		int i = 1;
		Course* CourseCur = CourseHead;
		int t = 0;
		ViewCourse(CourseCur, t, i);
		t++;
		i--;
		cout << "Register(0.stop): ";
		cin >> opt;
		while (opt > i || opt < 0)
		{
			cout << "Error. Register again: ";
			cout << "     ";
			cin >> opt;
			if (opt == 0)return;
		}

		if (opt == 0) return;


		int count = 1;
		while (CourseCur != nullptr && count != opt)
		{

			CourseCur = CourseCur->pNext;
			count++;

		}

		if (CourseCur != nullptr)
		{
			Course* EnrollMove = YearCur->CLass[j].Stu[k].Registered;
			while (EnrollMove != nullptr)
			{
				if (EnrollMove->Day1 == CourseCur->Day1)
				{
					if (EnrollMove->Session1 == CourseCur->Session1)
					{
						cout << "Conflicted with another course. Register again: " << endl;
						goto Enroll;
					}
				}
				if (EnrollMove->Day2 == CourseCur->Day2)
				{
					if (EnrollMove->Session2 == CourseCur->Session2)
					{
						cout << "Conflicted with another course. Register again:" << endl;
						goto Enroll;
					}
				}

				EnrollMove = EnrollMove->pNext;

			}
			Data* InfoMove = CourseCur->DataOfStu;
			while (InfoMove != nullptr && InfoMove->StudentID != YearCur->CLass[j].Stu[k].StudentID)
			{
				InfoMove = InfoMove->pNext;
			}

			if (InfoMove == nullptr && EnrollMove == nullptr)
			{
				if (CourseCur->NumOfStu < CourseCur->MaxStu)
				{

					Data* temp = new Data;
					temp->j = j;
					temp->k = k;
					temp->StudentID = YearCur->CLass[j].Stu[k].StudentID;
					temp->FirstName = YearCur->CLass[j].Stu[k].FirstName;
					temp->Name = YearCur->CLass[j].Stu[k].Name;
					temp->pNext = nullptr;


					if (CourseCur->DataOfStu == nullptr || CourseCur->DataOfStu->StudentID > temp->StudentID)
					{
						temp->pNext = CourseCur->DataOfStu;
						CourseCur->DataOfStu = temp;
					}
					else
					{
						InfoCur = CourseCur->DataOfStu;

						while (InfoCur->pNext != nullptr && InfoCur->pNext->StudentID < temp->StudentID)
						{
							InfoCur = InfoCur->pNext;
						}


						temp->pNext = InfoCur->pNext;
						InfoCur->pNext = temp;
					}


					if (ListEnroll != nullptr)
					{
						ListEnroll->pNext = new Course;
						ListEnroll = ListEnroll->pNext;
					}

					else
					{

						YearCur->CLass[j].Stu[k].Registered = new Course;
						ListEnroll = YearCur->CLass[j].Stu[k].Registered;
					}

					ListEnroll->CourseID = CourseCur->CourseID;
					ListEnroll->NameOfCourse = CourseCur->NameOfCourse;
					ListEnroll->NameOfTeacher = CourseCur->NameOfTeacher;
					ListEnroll->NumOfCredit = CourseCur->NumOfCredit;
					ListEnroll->Day1 = CourseCur->Day1;
					ListEnroll->Session1 = CourseCur->Session1;
					ListEnroll->Day2 = CourseCur->Day2;
					ListEnroll->Session2 = CourseCur->Session2;

					NumOfOpt++;
					CourseCur->NumOfStu++;
					ListEnroll->NumOfStu = CourseCur->NumOfStu;

					ListEnroll->pNext = nullptr;

				}

				else
				{
					cout << "Course is full. Register again: " << endl;
					goto Enroll;
				}

			}
			else
			{
				cout << "You have registered this course. Register again: " << endl;
				goto Enroll;
			}

		}

	}
}

void ViewListEnrolled(Schoolyear* YearCur, int x)
{
	int i = 1;
	int j = (x / 100) - 1;
	int k = (x % 100) - 1;
	Course* CourseCur = YearCur->CLass[j].Stu[k].Registered;
	while (CourseCur != nullptr)
	{
		cout << i << "." << CourseCur->CourseID << endl;
		cout << CourseCur->NameOfCourse << endl;
		cout << CourseCur->NameOfTeacher << endl;
		cout << CourseCur->NumOfCredit << endl;
		cout << CourseCur->Day1 << '/' << CourseCur->Session1 << endl;
		cout << CourseCur->Day2 << '/' << CourseCur->Session2 << endl;
		cout << CourseCur->NumOfStu << '/' << CourseCur->MaxStu << endl;
		CourseCur = CourseCur->pNext;
		i++;
	}
}

void RemoveCourseEnrolled(Schoolyear* YearCur, Course* CourseHead, int x)
{
	int j = (x / 100) - 1;
	int k = (x % 100) - 1;
	Data* InfoCur = nullptr;
	Course* ListEnroll = YearCur->CLass[j].Stu[k].Registered;
	Course* CourseCur = CourseHead;
	if (ListEnroll == nullptr) return;
	int optRemv, t = 0, i = 1;
	ViewCourse(ListEnroll, t, i);
	t++; i--;
	cout << "Input num of the course to remove:";
	cin >> optRemv;
	Course* temp = nullptr;
	if (optRemv == 1)
	{
		YearCur->CLass[j].Stu[k].Registered = YearCur->CLass[j].Stu[k].Registered->pNext;
		temp = ListEnroll;
	}
	else
	{
		int count = 1;
		while (ListEnroll->pNext != nullptr && count != optRemv - 1)
		{
			ListEnroll = ListEnroll->pNext;
			count++;
		}

		if (ListEnroll->pNext != nullptr)
		{
			temp = ListEnroll->pNext;
			ListEnroll->pNext = temp->pNext;
		}
	}


	while (CourseCur != nullptr && CourseCur->CourseID != temp->CourseID)
	{
		CourseCur = CourseCur->pNext;
	}

	delete temp;

	if (CourseCur != nullptr)
	{
		InfoCur = CourseCur->DataOfStu;

		if (InfoCur->StudentID == YearCur->CLass[j].Stu[k].StudentID)
		{

			CourseCur->DataOfStu = CourseCur->DataOfStu->pNext;
			delete InfoCur;
		}
		else
		{
			while (InfoCur->pNext != nullptr && InfoCur->pNext->StudentID != YearCur->CLass[j].Stu[k].StudentID)
			{
				InfoCur = InfoCur->pNext;
			}

			if (InfoCur->pNext != nullptr)
			{
				Data* temp = InfoCur->pNext;
				InfoCur->pNext = temp->pNext;
				delete temp;
			}
		}
		CourseCur->NumOfStu--;
		YearCur->CLass[j].Stu[k].NumOfOpt--;
	}
	cout << "Remove course succesfully." << endl;
}

void ViewListClasses(Schoolyear* YearCur)
{
	//thêm gotoxy và kẻ khung, thêm hàm Back()
	string year = "";
	cout << "Enter the year you want to view class: ";
	cin >> year;
	cout << endl;
	while (YearCur != nullptr)
	{
		if (year == YearCur->NumOfYear)
		{
			for (int i = 0; i < YearCur->NumOfClass; i++)
			{
				cout << i + 1 << "." << YearCur->CLass[i].NameOfClass;
				cout << endl;
			}

			break;
		}
		YearCur = YearCur->YearNext;
	}
	if (YearCur == nullptr)
	{
		cout << "The entered year is not available" << endl;
	}

}

void ViewListStudentInClass(Schoolyear* YearCur)
{
	string NameClass = "";
	cout << "Enter the name class you want to view: ";
	getline(cin, NameClass);
	char keycap = 75;
	while (YearCur != nullptr)
	{
		for (int i = 0; i < YearCur->NumOfClass; i++)
		{
			if (NameClass == YearCur->CLass[i].NameOfClass)
			{
				while (keycap != 13)
				{
					if (keycap == 75)
					{
						/*clear();*/
						/*gotoxy(51, 9);*/
						cout << NameClass;
						for (int j = 0; j < YearCur->CLass[i].NumOfStudent / 2; j++)
						{
							/*gotoxy(15, j + 10);*/
							cout << YearCur->CLass[i].Stu[j].Num;
							/*gotoxy(19, j + 10);*/
							cout << YearCur->CLass[i].Stu[j].StudentID;
							/*gotoxy(30, j + 10);*/
							cout << YearCur->CLass[i].Stu[j].FirstName;
							/*gotoxy(31 + YearCur->CLass[i].Stu[j].FirstName.length(), j + 10);*/
							cout << YearCur->CLass[i].Stu[j].Name;
							/*gotoxy(57, j + 10);*/
							cout << YearCur->CLass[i].Stu[j].Sex;
							/*gotoxy(65, j + 10);*/
							cout << YearCur->CLass[i].Stu[j].DOB;
							/*gotoxy(79, j + 10);*/
							cout << YearCur->CLass[i].Stu[j].ID;

						}
						keycap = getch();
						if (keycap == -32) keycap = getch();
					}
					if (keycap == 77)
					{
						/*clear();*/
						/*gotoxy(51, 9);*/
						cout << NameClass;
						int j = YearCur->CLass[i].NumOfStudent / 2;
						int k = 0;

						while (j < YearCur->CLass[i].NumOfStudent)
						{
							/*gotoxy(15, k + 10);*/
							cout << YearCur->CLass[i].Stu[j].Num;
							/*gotoxy(19, k + 10);*/
							cout << YearCur->CLass[i].Stu[j].StudentID;
							/*gotoxy(30, k + 10);*/
							cout << YearCur->CLass[i].Stu[j].FirstName;
							/*gotoxy(31 + YearCur->CLass[i].Stu[j].FirstName.length(), k + 10);*/
							cout << YearCur->CLass[i].Stu[j].Name;
							/*gotoxy(57, k + 10);*/
							cout << YearCur->CLass[i].Stu[j].Sex;
							/*gotoxy(65, k + 10);*/
							cout << YearCur->CLass[i].Stu[j].DOB;
							/*gotoxy(79, k + 10);*/
							cout << YearCur->CLass[i].Stu[j].ID;
							j++;
							k++;
						}
						keycap = getch();
						if (keycap == -32) keycap = getch();
					}
				}
				return;
			}
		}
		YearCur = YearCur->YearNext;
	}
	if (YearCur == nullptr)
	{
		cout << "The entered name of is not available" << endl;
	}
}

void ViewListStudentInCourse(Schoolyear* YearCur, int sem)
{
	string CourseID = "";
	cout << "Enter the course ID you want to view:";
	getline(cin, CourseID);
	Course* CourseCur = YearCur->Sem[sem].pCourse;
	while (CourseCur != nullptr)
	{
		if (CourseID == CourseCur->CourseID)
		{
			Data* Cur;
			char keycap = 75;
			while (keycap != 13)
			{
				Cur = CourseCur->DataOfStu;
				if (keycap == 75)
				{
					/*clear();*/
					int k = 1;
					/*gotoxy(40, 9);*/
					cout << "NUM  STUDENT ID  NAME";
					while (k <= CourseCur->NumOfStu / 2)
					{
						/*gotoxy(40, k + 10);*/
						cout << k << " " << Cur->StudentID << "\t" << Cur->FirstName << " " << Cur->Name;
						Cur = Cur->pNext;
						k++;
					}
				}
				keycap = getch();
				if (keycap == -32) keycap = getch();
				if (keycap == 77)
				{
					/*clear();*/
					int k = CourseCur->NumOfStu / 2 + 1;
					/*gotoxy(40, 9);*/
					cout << "NUM  STUDENT ID  NAME";
					while (k <= CourseCur->NumOfStu)
					{
						/*gotoxy(40, k + 10 - CourseCur->NumOfStu / 2 - 1);*/
						cout << k << " " << Cur->StudentID << "\t" << Cur->FirstName << " " << Cur->Name;
						Cur = Cur->pNext;
						k++;
					}
				}
				do {
					keycap = getch();
					if (keycap == -32) keycap = getch();
				} while (keycap != 75 && keycap != 13);
			}
			return;
		}
		CourseCur = CourseCur->pNext;
	}
	if (CourseCur == nullptr)
	{
		/*txtColor(4);
		gotoxy(51, 12);*/
		cout << "The entered course is not available" << endl;
		/*txtColor(7);*/
	}
}

void ExportListStudentCourse(Course* CourseHead)
{
	Course* CourseCur = CourseHead;

	string CourseID;
	ofstream output;

	cout << "Input course ID: ";

	getline(cin, CourseID);

	output.open(CourseID + ".csv", ofstream::out);


	while (CourseCur != nullptr && CourseCur->CourseID != CourseID)
	{
		CourseCur = CourseCur->pNext;
	}

	if (CourseCur != nullptr)
	{
		Data* InfoCur = CourseCur->DataOfStu;
		int i = 1;
		while (InfoCur != nullptr)
		{
			output << i << ',' << InfoCur->StudentID << ',' << InfoCur->FirstName << ',' << InfoCur->Name << endl;
			InfoCur = InfoCur->pNext;
		}

		if (InfoCur == nullptr) cout << "Export successfully!";
		else cout << "Export fail";
	}

}

void LoadScoreboard(Course*& CourseHead, Schoolyear*& YearCur)
{

	ifstream input;
	string CourseID;
	Course* CourseCur = CourseHead;
	Data* InfoCur = nullptr;
	cout << "Input course ID: ";
	getline(cin, CourseID);
	input.open(CourseID + ".csv", ifstream::in);
	if (!input.is_open())
	{
		cout << "Cannot open this file!";
	}
	else
	{
		while (!input.eof())
		{
			while (CourseCur != nullptr && CourseCur->CourseID != CourseID)
			{
				CourseCur = CourseCur->pNext;
			}

			InfoCur = CourseCur->DataOfStu;

			if (InfoCur == nullptr) return;
			while (InfoCur != nullptr)
			{
				input.ignore(1000, ',');
				input.ignore(1000, ',');
				input.ignore(1000, ',');
				input.ignore(1000, ',');
				getline(input, InfoCur->Score.Total, ',');
				getline(input, InfoCur->Score.Final, ',');
				getline(input, InfoCur->Score.Midterm, ',');
				getline(input, InfoCur->Score.Other);


				Course* EnrollList = YearCur->CLass[InfoCur->j].Stu[InfoCur->k].Registered;

				while (EnrollList != nullptr && EnrollList->CourseID != CourseCur->CourseID)
				{
					EnrollList = EnrollList->pNext;
				}

				if (EnrollList != nullptr)
				{
					EnrollList->Score.Total = InfoCur->Score.Total;
					EnrollList->Score.Final = InfoCur->Score.Final;
					EnrollList->Score.Midterm = InfoCur->Score.Midterm;
					EnrollList->Score.Other = InfoCur->Score.Other;
				}

				InfoCur = InfoCur->pNext;

			}
			if (InfoCur == nullptr) cout << "Export successfully";
			else cout << "Export fail";
		}

	}


	input.close();
}

void ViewScoreboardCourse(Course* CourseHead)
{
	string NameOfCourse;
	Course* CourseCur = CourseHead;
	Data* InfoCur = nullptr;
	cout << "Input name of course: ";
	cin.ignore();
	getline(cin, NameOfCourse);

	while (CourseCur != nullptr && CourseCur->NameOfCourse != NameOfCourse)
	{
		CourseCur = CourseCur->pNext;
	}

	InfoCur = CourseCur->DataOfStu;
	if (InfoCur == nullptr) return;
	int i = 1;
	cout << left << setw(4) << "No" << left << setw(12) << "StudentID" << left << setw(25) << "FirstName" << left << setw(10) << "Name" << right << setw(12) << "Total Mark" << right << setw(12) << "Final Mark" << right << setw(14) << "Midterm Mark" << right << setw(12) << "Other Mark" << endl;
	while (InfoCur != nullptr)
	{

		cout << left << setw(4) << i << left << setw(12) << InfoCur->StudentID << left << setw(25) << InfoCur->FirstName << left << setw(10) << InfoCur->Name << right << setw(12) << InfoCur->Score.Total << right << setw(12) << InfoCur->Score.Final << right << setw(14) << InfoCur->Score.Midterm << right << setw(12) << InfoCur->Score.Other << endl;
		InfoCur = InfoCur->pNext;
		i++;
	}

}

void ViewScoreboardClass(Schoolyear* YearCur, int x)
{
	int j = (x / 100) - 1;
	string NameOfCourse;
	cout << "Input name of course: ";
	cin.ignore();
	getline(cin, NameOfCourse);


	cout << left << setw(4) << "Num" << left << setw(12) << "Student ID" << left << setw(25) << "FirstName" << left << setw(10) << "Name" << right << setw(12) << "GPA Total" << right << setw(12) << "GPA Final" << endl;
	for (int i = 0; i < YearCur->CLass[x].NumOfStudent; i++)
	{
		Course* EnrollList = YearCur->CLass[j].Stu[i].Registered;

		while (EnrollList != nullptr && EnrollList->NameOfCourse != NameOfCourse)
		{
			EnrollList = EnrollList->pNext;
		}

		if (EnrollList != nullptr)
			cout << left << setw(4) << i + 1 << left << setw(12) << YearCur->CLass[j].Stu[i].StudentID << left << setw(25) << YearCur->CLass[j].Stu[i].FirstName << left << setw(10) << YearCur->CLass[j].Stu[i].Name << right << setw(12) << EnrollList->Score.Total << right << setw(12) << EnrollList->Score.Final << endl;

	}


}

void ViewScoreboardStu(Schoolyear* YearCur, int x)
{
	int j = (x / 100) - 1;
	int k = (x % 100) - 1;
	Course* EnrollList = YearCur->CLass[j].Stu[k].Registered;
	cout << left << setw(4) << "No" << left << setw(12) << "StudentID" << left << setw(25) << "FirstName" << left << setw(10) << "Name" << right << setw(12) << "Total Mark" << right << setw(12) << "Final Mark" << right << setw(14) << "Midterm Mark" << right << setw(12) << "Other Mark" << endl;
	while (EnrollList != nullptr)
	{
		cout << left << setw(4) << YearCur->CLass[j].Stu[k].Num << left << setw(12) << YearCur->CLass[j].Stu[k].StudentID << left << setw(25) << YearCur->CLass[j].Stu[k].FirstName << left << setw(10) << YearCur->CLass[j].Stu[k].Name << right << setw(12) << EnrollList->Score.Total << right << setw(12) << EnrollList->Score.Final << right << setw(14) << EnrollList->Score.Midterm << right << setw(12) << EnrollList->Score.Other << endl;
		EnrollList = EnrollList->pNext;
	}
}

//void UpdateStudentResult(Schoolyear*& YearCur, Course*& CourseHead)
//{
//	int opt;
//	string StudentID;
//	string NameOfCourse;
//
//	cout << "Input Name of Course: ";
//	cin.ignore();
//	getline(cin, NameOfCourse);
//
//	cout << "Input Student ID: ";
//	cin.ignore();
//	getline(cin, StudentID);
//	do
//	{
//
//
//		cout << "UPDATE STUDENT RESULT" << endl;
//		cout << "1.Other Mark" << endl;
//		cout << "2.Midterm Mark" << endl;
//		cout << "3.Final Mark" << endl;
//		cout << "4.Total Mark" << endl;
//		cout << "0 to stop." << endl;
//		cout << "Input your option: ";
//		cin >> opt;
//
//		Course* CourseCur = CourseHead;
//		Data* InfoCur = nullptr;
//		Course* EnrollList = nullptr;
//		while (CourseCur != nullptr && CourseCur->NameOfCourse != NameOfCourse)
//		{
//			CourseCur = CourseCur->pNext;
//		}
//		if (CourseCur != nullptr)
//		{
//			InfoCur = CourseCur->DataOfStu;
//			while (InfoCur != nullptr && InfoCur->StudentID != StudentID)
//			{
//				InfoCur = InfoCur->pNext;
//			}
//
//			EnrollList = YearCur->CLass[InfoCur->j].Stu[InfoCur->k].Registered;
//			while (EnrollList != nullptr && EnrollList->NameOfCourse != NameOfCourse)
//			{
//				EnrollList = EnrollList->pNext;
//			}
//		}
//
//		string change;
//		switch (opt)
//		{
//		case 1:
//
//
//			cout << "Input your change: ";
//			cin >> change;
//			if (InfoCur != nullptr && EnrollList != nullptr)
//			{
//				InfoCur->Score.Other = change;
//				EnrollList->Score.Other = change;
//			}
//			break;
//		case 2:
//
//			cout << "Input your change: ";
//			cin >> change;
//			if (InfoCur != nullptr && EnrollList != nullptr)
//			{
//				InfoCur->Score.Midterm = change;
//				EnrollList->Score.Midterm = change;
//			}
//			break;
//		case 3:
//
//			cout << "Input your change: ";
//			cin >> change;
//			if (InfoCur != nullptr && EnrollList != nullptr)
//			{
//				InfoCur->Score.Final = change;
//				EnrollList->Score.Final = change;
//			}
//			break;
//		case 4:
//			cout << "Input your change: ";
//			cin >> change;
//			if (InfoCur != nullptr && EnrollList != nullptr)
//			{
//				InfoCur->Score.Total = change;
//				EnrollList->Score.Total = change;
//			}
//			break;
//		}
//	} while (opt != 0);
//}