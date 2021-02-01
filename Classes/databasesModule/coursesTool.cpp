#include "coursesTool.h"

using namespace cardsApp::databasesModule;
using namespace cardsApp::localProfile;


coursesTool::coursesTool() {
	auto test = GET_DATABASE_MANAGER().getDatabase<cardsApp::databasesModule::coursesDatabase>("coursesDb");
}

coursesTool::~coursesTool() {

}

void coursesTool::getCoursesWithProgress() {

}
