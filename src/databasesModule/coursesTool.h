#ifndef CARDS_APP_COURSESTOOL_H
#define CARDS_APP_COURSESTOOL_H

#include "cocos2d.h"
#include <map>
#include <string>
#include <tuple>
#include <vector>
// all profile block header
#include "common/profileModule/profileManager.h"
#include "localProfile/localProfileBlock.h"
// all databases header
#include "common/databaseModule/databaseInterface.h"
#include "common/databaseModule/databaseManager.h"
#include "databasesModule/coursesDatabase.h"
#include "databasesModule/ipaDatabase.h"

namespace cardsApp::databasesModule {

    class coursesTool {
      public:
        coursesTool();
        ~coursesTool();
        std::map<int, std::pair<int, sCourseBook*>> getCoursesWithProgress();
        void setProgress(int courseId, int cardId, bool isCorrect = false);
        void resetProgress(int courseId);

      private:
        cardsApp::databasesModule::coursesDatabase* courseDb = nullptr;
        cardsApp::databasesModule::ipaDatabase* ipaDb = nullptr;
        cardsApp::localProfile::localProfileBlock* localProfile = nullptr;
    };
}// namespace cardsApp::databasesModule


#endif// CARDS_APP_COURSESTOOL_H
