#ifndef CARDS_APP_IPADATABASE_H
#define CARDS_APP_IPADATABASE_H

#include "cocos2d.h"
#include "common/databaseModule/databaseInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <map>
#include <string>
#include <vector>

namespace cardsApp::databasesModule {

    typedef std::map<std::string, std::string> sLetter;

    class ipaDatabase : public common::databaseModule::databaseInterface {
      public:
        ipaDatabase();
        ~ipaDatabase() = default;
        void load(const rapidjson::Document&) override;
        const std::string& findString(const std::string&) const;

      protected:
        bool loadDictionary(const std::string&, const rapidjson::Document&);

      private:
        std::map<std::string, sLetter> stringMapDb;
    };
}// namespace cardsApp::databasesModule


#endif// CARDS_APP_IPADATABASE_H
