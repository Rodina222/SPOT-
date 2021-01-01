#include "Registrar.h"
#include <iostream>
#include <fstream>
#include<sstream>
#include<string.h>
#include<vector>
#include"Rules.h"
#include "Actions/ActionAddCourse.h"
#include"ActionSavePlan.h"

using namespace std;

Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
	//LoadCatalog();
	
}


//returns a pointer to GUI
GUI* Registrar::getGUI() const
{
	return pGUI;
}

//returns the study plan
StudyPlan* Registrar::getStudyPlay() const
{
	return pSPlan;
}
//string CourseTitle;
//string CourseType;
//string Coreqlist;
//string prerequisit;

//CourseInfo Registrar::getCourseInfo(Course* course)  const
//{
//	CourseInfo COURSE_INFO;
//	for (int i = 0; i < RegRules.CourseCatalog.size(); i++) 
//	{
//		if (RegRules.CourseCatalog[i].Code == course->getCode())
//		{
//			 COURSE_INFO.Code=course->getCode();
//
//			COURSE_INFO.Title=course->getTitle();
//
//		    COURSE_INFO.Credits= course->getCredits();
//
//			for (int t = 0; t < COURSE_INFO.PreReqList.size(); t++)
//			COURSE_INFO.PreReqList[t] = course->getPreReq();
//
//			for (int r = 0; r < COURSE_INFO.CoReqList.size(); r++)
//		   COURSE_INFO.CoReqList[r]= course->getCoReq();
//			
//		}
//		
//	}
//	return COURSE_INFO;
//}


Action* Registrar::CreateRequiredAction() 
{	
	ActionData actData = pGUI->GetUserAction("Pick and action...");
	Action* RequiredAction = nullptr;

	switch (actData.actType)
	{
	case ADD_CRS:	//add_course action
		RequiredAction = new ActionAddCourse(this);
		break;

	case SAVE: //save current study plan
		RequiredAction = new ActionSavePlan(this);
	  break;

	//TODO: Add case for each action
	
	case EXIT:
		break;
		
	}
	return RequiredAction;
}

//Executes the action, Releases its memory, and return true if done, false if cancelled
bool Registrar::ExecuteAction(Action* pAct)
{
	bool done = pAct->Execute();
	delete pAct;	//free memory of that action object (either action is exec or cancelled)
	return done;
}

void Registrar::Run()
{
	while (true)
	{
		//update interface here as CMU Lib doesn't refresh itself
		//when window is minimized then restored
		UpdateInterface();

		Action* pAct = CreateRequiredAction();
		if (pAct)	//if user doesn't cancel
		{
			if (ExecuteAction(pAct))	//if action is not cancelled
				UpdateInterface();
		}
	}
}


void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}
 

  void Registrar::SavePlan(ofstream& file)
{
	  pSPlan->SAVE(file);
	  
}


  
	  

  void Registrar::LoadCatalog()
  {

	  CourseInfo cinfo;

	  ifstream file;
	  file.open("D:\\CIE-year 2\\CIE 202 _C++\\ProjectFiles\\Catalog - 2020 12 19.txt");
	  if (!file.is_open())
	  {
		  cout << "File open failure!";
	  }
	  string LineOfCode = "";
	  string restofline = "";
	  string prereq = "";
	  string CRDS = "";
	  int crds = 0;
	  list<string>PreReqList;
	  list<string>CoReqList;

	  while (getline(file, LineOfCode))
	  {
		  //cout << LineOfCode << endl;
		  stringstream cc(LineOfCode);
		  getline(cc, cinfo.Code, ',');
		  //cout << cinfo.Code << endl;
		  getline(cc, cinfo.Title, ',');
		  //cout << cinfo.Title << endl;
		  getline(cc, CRDS, ',');
		  stringstream string_to_int(CRDS);//we declared the line as a string so this function makes casting for the number of credits to be an integer.
		  string_to_int >> crds;
		  cinfo.Credits = crds;
		  //cout << cinfo.Credits;

		  getline(cc, restofline, ',');
		  if (restofline.empty())
			  continue;

		  cout << restofline << endl;
		  stringstream ss(restofline);
		  string temp;
		  string course, num;
		  string coursecode;
		  ss >> temp;
		  if (temp == "Coreq:") {
			  while (temp != "") {
				  ss >> course;
				  ss >> num;
				  coursecode = course + " " + num;
				  CoReqList.push_back(coursecode);
				  ss >> temp;

			  }
			  cout << coursecode << endl;

		  }
		  cout << temp << endl;
		  ss >> temp;
		  cout << temp << endl;
		  ss >> temp;
		  cout << temp << endl;

		  getline(cc, restofline, ',');
		  if (restofline.empty())
			  continue;

		  cout << restofline << endl;
		  stringstream rr(restofline);
		  string temporary;
		  string coursee, number;
		  string ccode;
		  rr >> temporary;
		  
			  while (temporary != "") {
				  rr >> coursee;
				  rr >> number;
				  ccode = coursee + " " + number;
				  PreReqList.push_back(ccode);
				  rr >> temporary;

			  }
			  cout << ccode << endl;

		  
		  cout << temporary << endl;
		  rr >> temporary;
		  cout << temporary << endl;
		  rr >> temporary;
		  cout << temporary << endl;
		 
		  RegRules.CourseCatalog.push_back(cinfo);
	  }

	  file.close();
  }

  list<Course_Code> Registrar::getCatalogPrereq(string coursecode)
  {

	  for (int i = 0; i < RegRules.CourseCatalog.size(); i++)
	  {
		  if (RegRules.CourseCatalog[i].Code == coursecode && !RegRules.CourseCatalog[i].PreReqList.empty())
		  {
			  return RegRules.CourseCatalog[i].PreReqList;
		  }
	  }
  }

  list<Course_Code> Registrar::getCatalog_Corereq(string coursecode)
  {

	  for (int i = 0; i < RegRules.CourseCatalog.size(); i++)
	  {
		  if (RegRules.CourseCatalog[i].Code == coursecode && !RegRules.CourseCatalog[i].CoReqList.empty())
		  {
			  return RegRules.CourseCatalog[i].CoReqList;
		  }
	  }
  }

	


	  Registrar::~Registrar()
	  {
		  delete pGUI;
		  delete pSPlan;
		  delete pcourse;



	  }
	




	
	
		
	



	





