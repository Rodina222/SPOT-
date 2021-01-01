#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"


//The maestro class for the application
#pragma once

class Registrar
{
	GUI *pGUI;	//pointer to GUI 
	Rules RegRules;	//Registration rules
	StudyPlan *pSPlan;
	Course *pcourse;//by me
	

public:
	Registrar();
	GUI* getGUI() const;
	Action* CreateRequiredAction();
	bool ExecuteAction(Action*);
	void UpdateInterface();
	StudyPlan* getStudyPlay() const;
	//CourseInfo getCourseInfo(Course*) const; //by me
	void LoadCatalog(); //by me
	list<Course_Code> getCatalogPrereq(string coursecode);
	list<Course_Code> Registrar::getCatalog_Corereq(string coursecode);
	void SavePlan(ofstream& filename);


	void Run();

	~Registrar();
};

