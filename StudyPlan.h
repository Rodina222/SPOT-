#pragma once
#include <vector>
#include "AcademicYear.h"
#include "../GUI/Drawable.h"


//A full study plan for as student
class StudyPlan:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	struct Warnings {
		vector<string> moderate;
		vector<string> credits;
		vector<string> uniCOMIssues;
		vector<string> TrackCOMIssues;
		vector<string> electiveIssues;
		vector<string> MajorCOMIssues;
		vector<string> EleComIssues;
		vector<string> Prereqwarning;
		vector<string>Coreqwarning;
	};
	AcademicYear* pAcademicYear;//by me

	vector<AcademicYear*> plan;	//plan is a list of academic years
	string PlanNotes;
	Warnings  planWarning;

protected:
	Registrar* Preg;

	
	
public:
	StudyPlan();
	bool AddCourse(Course*, int year, SEMESTER);
	void virtual DrawMe(GUI*) const;
	void SAVE(ofstream& filename);
	Course* findCourseCode(int X_coor, int Y_coor);
	virtual ~StudyPlan();
	//Warnings getWarnings() const;
	void Check_Prereq_Validity();
	void CheckCoreq_Validity();
};

