#include "staff.h"
#include <string>

int main()
{
	Schoolyear* YearHead = NULL, * YearCur1 = NULL, * YearCur2 = NULL;
	Teacher* Staff;
	string username, password;
	Date Today;
	Now(Today);
	int option1, NumOfStaff, sem = 0;
	InputStaff(Staff, NumOfStaff);
	do
	{
		Now(Today);
		InputAccount(username, password);
		int x = CheckLogin(username, password, YearCur1, Staff, NumOfStaff);
		if (x == 0)
		{
			cout << "Your username or password is incorrect!!!" << endl;
			password = "";
			YearCur1 = YearHead;
			continue;
		}
		else
		{
			cout << "You log in successfully!!!" << endl << endl;
		}
		string* str1;
		int k;
		if (x < 100)k = 9;
		else
		{
			if (CheckDateRegister(Today, YearCur2->Sem[sem].StartReg, YearCur2->Sem[sem].EndReg)) k = 6;
			else k = 4;
			if (CheckImport(YearCur1, x)) k = 5;
		}
		str1 = new string[k];
		str1[0] = "Log out";
		str1[1] = "View info";
		str1[2] = "Change password";
		if (x < 100)
		{
			str1[3] = "Add new year";
			str1[4] = "Add new semester";
			str1[5] = "Course";
			str1[6] = "View classes in a year";
			str1[7] = "View students in a class";
			str1[8] = "View students in a course";
		}
		else
		{
			if (CheckDateRegister(Today, YearCur2->Sem[sem].StartReg, YearCur2->Sem[sem].EndReg))
			{
				str1[3] = "Register course";
				str1[4] = "View list of enrolled courses";
				str1[5] = "Remove a course from the enrolled list";
			}
			else str1[3] = "View course registered";
			if (CheckImport(YearCur1, x)) str1[4] = "View your scoreboard";
		}
		int option1 = 1;
		while (option1 != 0)
		{
			for (int i = 1; i < k; i++) {
				cout << i << ". " << str1[i] << endl;
			}
			cout << "0. " << str1[0] << endl;
			cout << "Input your option: ";
			cin >> option1;
			switch (option1)
			{
				case 1:
				{
					system("cls");
					ViewIn(x, YearCur1, Staff);
					break;
				}
				case 2:
				{
					system("cls");
					ChangePass(YearCur1, Staff, x, NumOfStaff);  
					break;
				}
				case 3:
				{
					system("cls");
					if (x < 100)
					{
						if (YearHead == nullptr)
						{
							AddYear(YearHead);
							YearCur1 = YearHead;
						}
						else
						{
							AddYear(YearCur1->YearNext);
							YearCur1 = YearCur1->YearNext;
						}
					}
					else
					{
						if (CheckDateRegister(Today, YearCur2->Sem[sem].StartReg, YearCur2->Sem[sem].EndReg))
							CourseEnroll(YearCur1, YearCur2->Sem[sem].pCourse, x, YearCur1->CLass[x / 100 - 1].Stu[x % 100 - 1].NumOfOpt);
						else
						{
							int t, i;
							ViewCou(YearCur1->CLass[x / 100 - 1].Stu[x % 100 - 1].Registered, t, i);
						}
					}
					break;
				}
				case 4:
				{
					system("cls");
					if (x < 100)
					{
						YearCur2 = YearHead;
						AddSem(YearCur2, sem);
					}
					else
					{
						int t, i;
						ViewCou(YearCur1->CLass[x / 100 - 1].Stu[x % 100 - 1].Registered, t, i);
					}
					break;
				}
				case 5:
				{
					system("cls");
					if (x < 100)
					{
						int t;
						string* str2;
						if (CheckDateEndSemester(Today, YearCur2->Sem[sem].EndSem))
							t = 10;
						else
							t = 5;
						str2 = new string[t];
						str2[0] = "Back";
						str2[1] = "Add new course";
						str2[2] = "View list of course";
						str2[3] = "Update course information";
						str2[4] = "Delete a course";
						if (CheckDateEndSemester(Today, YearCur2->Sem[sem].EndSem))
						{
							str2[5] = "Export list of students  in a course";
							str2[6] = "Import the scoreboard of a course";
							str2[7] = "View the scoreboard of a course";
							str2[8] = "Update a student result";
							str2[9] = "View the scoreboard of a class";
						}
						int option2 = 1;
						while (option2 != 0)
						{
							for (int i = 1; i < t; i++) {
								cout << i << ". " << str2[i] << endl;
							}
							cout << "0. " << str2[0] << endl;
							cout << "Input your option: ";
							cin >> option2;
							switch (option2)
							{
								case 1:
								{
									system("cls");
									AddCou(YearCur2->Sem[sem].pCourse);
									break;
								}
								case 2:
								{
									system("cls");
									int t;
									ViewCou(YearCur2->Sem[sem].pCourse, t, t);
									break;
								}
								case 3:
								{
									system("cls");
									UpdateCou(YearCur2, sem);
									break;
								}
								case 4:
								{
									system("cls");
									DeleteCou(YearCur2, sem);
									break;
								}
								case 5:
								{
									system("cls");
									ExportListStudentCourse(YearCur2->Sem[sem].pCourse);
									break;
								}
								case 6:
								{
									system("cls");
									LoadScoreboard(YearCur2->Sem[sem].pCourse, YearHead);
									break;
								}
								case 7:
								{
									system("cls");
									ViewScoreboardCourse(YearCur2->Sem[sem].pCourse);
									break;
								}
								case 8:
								{
									system("cls");
									break;
								}
								case 9:
								{
									system("cls");
									break;
								}
							}
						}
						delete[]str2;
					}
					else
					{
						RemoveCourseEnrolled(YearCur1, YearCur2->Sem[sem].pCourse, x);
					}
					break;
				}
				case 6:
				{
					system("cls");
					ViewListClasses(YearHead);
					break;
				}
				case 7:
				{
					system("cls");
					ViewListStudentInClass(YearHead);
					break;
				}
				case 8:
				{
					system("cls");
					ViewListStudentInCourse(YearCur2, sem);
					break;
				}
				case 0:
				{
					YearCur1 = YearHead;
					break;
				}
			}
			password = "";
		}
		delete[]str1;
	} while (true);
	delete[]Staff;
	return 0;
}