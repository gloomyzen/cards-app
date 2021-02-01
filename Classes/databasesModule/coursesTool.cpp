#include "coursesTool.h"

using namespace cardsApp::databasesModule;
using namespace cardsApp::localProfile;


coursesTool::coursesTool() {
	courseDb = GET_DATABASE_MANAGER().getDatabase<coursesDatabase>("coursesDb");
	ipaDb = GET_DATABASE_MANAGER().getDatabase<ipaDatabase>("ipaDb");
	localProfile = GET_PROFILE().getBlock<localProfileBlock>("local");
}

coursesTool::~coursesTool() {}

void coursesTool::getCoursesWithProgress() {
//	auto courseDb->getCourses();
	auto test = ipaDb->findString("auto");
	auto light = ipaDb->findString("light");
	auto key = ipaDb->findString("key");
	auto ship = ipaDb->findString("ship");
	auto test2 = "";
}
