#include "StudyPlan.h"
#include "AcademicYear.h"
#include "../Registrar.h"
#include<iostream>
#include<fstream>
using namespace std;



StudyPlan::StudyPlan()
{
	//By default, the study plan starts with 5 years+

	//More year can be added
	for (int i = 0; i < 5; i++)
		plan.push_back(new AcademicYear);
}




//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 

	plan[year - 1]->AddCourse(pC, sem);
	
	return true;
}

void StudyPlan::DrawMe(GUI* pGUI) const
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++)
		plan[i]->DrawMe(pGUI);
}
void StudyPlan::SAVE(ofstream& file)
{
	
	for (int r = 0; r < plan.size(); r++)
	{
		
		file << "year" << r + 1;
		 pAcademicYear= plan[r];
		pAcademicYear->SAVE(file);
		cout << endl;

		
		
	}
	
	
}

Course* StudyPlan::findCourseCode(int X_coor, int Y_coor)
{
	
	for (int r = 0; r < plan.size(); r++)
	{
		Course* p_course =pAcademicYear->getCourseCode(X_coor, Y_coor);
		if (p_course != nullptr)
			return p_course;
	}
	return nullptr;
}



void StudyPlan::Check_Prereq_Validity() //compare the Prerequisites of a certain course in the study plan of the student with that is found in the course catalog
{
	string Result;
	list<Course_Code> prereqlist;
	for (int j = 0; j < plan.size(); j++)
	{
		Course* pCOURSE = pAcademicYear->Return_Course_Pointer();//returns pointer on every course in the study plan.

		prereqlist = Preg->getCatalogPrereq(pCOURSE->getCode());

		while (!prereqlist.empty())
		{
			if (prereqlist != pCOURSE->getPreReq())
			{

				Result = "There are Problems found in Prerequisits of the course! ";

				planWarning.Prereqwarning.push_back(pCOURSE->getCode());

			}
			else
			{
				Result = "No Problems are found in Prerequisits of the course.";
			}
		}
		
	}
}


void StudyPlan::CheckCoreq_Validity()  //compare the Corequisites of a certain course in the study plan of the student with that is found in the course catalog
{
	string Result;
	list<Course_Code> coreqlist;

	for (int j = 0; j < plan.size(); j++)
	{
		Course* pCOURSE = pAcademicYear->Return_Course_Pointer();//returns pointer on every course in the study plan.

		coreqlist = Preg->getCatalog_Corereq(pCOURSE->getCode());

		while (!coreqlist.empty())
		{
			if (coreqlist != pCOURSE->getCoReq())
			{
				Result = "There are Problems found in Corequisits of the course! ";

				planWarning.Coreqwarning.push_back(pCOURSE->getCode());
			}

			else
			{
				Result = "No Problems are found in Corequisits of the course.";

			}
		}
	}
}




StudyPlan::~StudyPlan()
{
	
	
}
