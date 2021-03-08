#ifndef CARDS_APP_COURSESDATABASE_H
#define CARDS_APP_COURSESDATABASE_H

#include "cocos2d.h"
#include "common/databaseModule/databaseInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <map>
#include <string>
#include <vector>

namespace cardsApp::databasesModule {

    struct sCourseCard {
        int id;
        std::string enWord;
        std::string enDescription;
        std::string enSentence;
        std::string ruWord;
        std::string ruSentence;
    };

    struct sCourseBook {
        int id;
        std::string name;
        std::map<int, sCourseCard*> cards;
        bool load(const rapidjson::Document&);
    };

    class coursesDatabase : public common::databaseModule::databaseInterface {
      public:
        coursesDatabase();
        ~coursesDatabase() = default;
        void load(const rapidjson::Document&) override;
        std::map<int, sCourseBook*> getCourses() { return coursesDb; }
        sCourseBook* getCourseById(int);

      private:
        std::map<int, sCourseBook*> coursesDb;
    };
}// namespace cardsApp::databasesModule


#endif// CARDS_APP_COURSESDATABASE_H
