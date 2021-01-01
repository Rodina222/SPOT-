#include "Course.h"
#include"../StudyPlan/AcademicYear.h"
#include "../GUI/GUI.h"
#include<iostream>
using namespace std;


Course::Course(Course_Code r_code, string r_title, int crd): code(r_code),Title(r_title)
{
	credits = crd;
}



Course* Course::get_Code(int X_coor,int Y_coor) 
{
	if ((X_coor <= (x_Coordinate+80))  && Y_coor <= (y_Coordinate+40))//CRS_WIDTH = 80,CRS_HEIGHT = 40
	{
		return this;
	}
	else
		return nullptr;
}

Course_Code Course::getCode() const
{
	return code;
}

string Course::getTitle() const
{
	return Title;
}

//return course credits
int Course::getCredits() const
{
	return credits;
}

string Course::getType() const
{
	return type;
}

list<Course_Code> Course::getPreReq() const
{

	return PreReq;
		
}

list<Course_Code> Course::getCoReq()  const
{
	
	return CoReq;
		
}


void Course::DrawMe(GUI* pG) const
{
	pG->DrawCourse(this);
}

int Course::getx_Coordinate() const
{
	return x_Coordinate;
}
int Course::gety_Coordinate() const
{
	return y_Coordinate;
}



void Course::SaveMe(ofstream& file)
{
	
	file << code << ",";
	file.close();
}

Course::~Course()
{

	
}

