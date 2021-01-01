#pragma once
#include <string>
#include <list>
#include <fstream>
using namespace std;
#include "..\DEFs.h"

#include "../GUI/Drawable.h"

//Base class for all types of courses
class Course : public Drawable
{
	const Course_Code code;	//course code: e.g. "CIE202". This is the course ID
	const string Title;		//course title: e.g. "Fundamentals of Computer Programming"
	int credits;	//no. of course credits
	const string type;	//Univ, track, or major.....etc.
	bool Done;		//Done or not yet?
	list<Course_Code> PreReq;	//list of prerequisites
	list<Course_Code> CoReq;	//list of prerequisites
	 int x_Coordinate;
	 int y_Coordinate;

public:
	
	Course(Course_Code r_code,string r_title, int crd);
	string getTitle() const;
	Course* get_Code(int X_coor, int Y_coor);
	Course_Code getCode() const;
	int getCredits() const;
	string getType() const;
	list<Course_Code> getPreReq() const;
	list<Course_Code> getCoReq() const;
	void DrawMe(GUI*) const;
	int getx_Coordinate() const;
	int gety_Coordinate() const;
	virtual ~Course();
   void  SaveMe(ofstream& file);

	

};
