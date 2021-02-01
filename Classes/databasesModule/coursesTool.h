#ifndef CARDS_APP_COURSESTOOL_H
#define CARDS_APP_COURSESTOOL_H

#include "cocos2d.h"
#include <string>
#include <map>
#include <vector>
//all profile block header
#include "common/profileModule/profileManager.h"
#include "localProfile/localProfileBlock.h"
//all databases header
#include "common/databaseModule/databaseInterface.h"
#include "common/databaseModule/databaseManager.h"
#include "databasesModule/coursesDatabase.h"
#include "databasesModule/ipaDatabase.h"

namespace cardsApp {
	namespace databasesModule {

		class coursesTool {
		public:
			coursesTool();
			~coursesTool();
			void getCoursesWithProgress();

		private:
			cardsApp::databasesModule::coursesDatabase* courseDb = nullptr;
			cardsApp::databasesModule::ipaDatabase* ipaDb = nullptr;
			cardsApp::localProfile::localProfileBlock* localProfile = nullptr;
		};
	}
}


#endif //CARDS_APP_COURSESTOOL_H
