#ifndef CARDS_APP_DATABASEMANAGER_H
#define CARDS_APP_DATABASEMANAGER_H

#include "common/databaseModule/databaseManagerInterface.h"
#include "common/databaseModule/databaseInterface.h"
#include <string>
#include <map>

#define GET_DATABASE_MANAGER() cardsApp::databasesModule::databaseManager::getInstance()

namespace cardsApp::databasesModule {
    class databaseManager : public common::databaseModule::databaseManagerInterface {
      public:
        enum class eDatabaseList {
            COURSES_DB = 0,
            IPA_DB,
        };
        databaseManager();
        ~databaseManager() override;

        static databaseManager& getInstance();
        void cleanup() override;

        void addDatabase(eDatabaseList id, std::string value, common::databaseModule::databaseInterface* db);

        template<typename T>
        T* getDatabase(eDatabaseList key) {
            return getRegisteredDatabase<T>(static_cast<int>(key));
        }
    };
}


#endif// CARDS_APP_DATABASEMANAGER_H
