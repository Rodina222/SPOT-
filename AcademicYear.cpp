#include "AcademicYear.h"
#include "..\Courses\Course.h"
#include "../GUI/GUI.h"
#include<iostream>
#include<fstream>
using namespace std;

AcademicYear::AcademicYear()
{
	

	//TODO: make all necessary initializations
}




//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem)
{
	//TODO:
	//This function still needs many checks to be compelete
	YearCourses[sem].push_back(pC);
	TotalCredits += pC->getCredits();

	//TODO: acording to course type incremenet corrsponding toatl hours for that year


	return true;
}


void AcademicYear::DrawMe(GUI* pGUI) const
{
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course
	
	for (int sem = FALL; sem < SEM_CNT; sem++)
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			(*it)->DrawMe(pGUI);	//call DrawMe for each course in this semester
		}
}

void AcademicYear::SAVE(ofstream& file)
{
	
	
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		
		file << sem << ",";

		for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course)
		{
			Course* PCourse;
			PCourse = *course;
			PCourse->SaveMe(file);
			

		}
		cout << endl;
		
	}
	
	
}

Course* AcademicYear::getCourseCode(int X_coor, int Y_coor)
{
	
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{


		for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course)
		{
			Course* pCourse;
			pCourse = *course;
			if (pCourse->get_Code(X_coor, Y_coor) != nullptr)
				return pCourse;
			 

		}	

	}
	return nullptr;
}

Course* AcademicYear::Return_Course_Pointer()
{
	
	Course* pCOURSE;
	

	for (int sem = FALL; sem < SEM_CNT; sem++)
	{

		
		for (auto course = YearCourses[sem].begin(); course != YearCourses[sem].end(); ++course)
		{
			pCOURSE = *course;

          //coursecode = pCOURSE->getCode();

				//return  coursecode;
			return pCOURSE;

		}

	}

}



AcademicYear::~AcademicYear()
{

}