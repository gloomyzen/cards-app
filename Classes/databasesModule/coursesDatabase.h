#ifndef CARDS_APP_COURSESDATABASE_H
#define CARDS_APP_COURSESDATABASE_H

#include "common/databaseModule/databaseInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include "cocos2d.h"
#include <string>
#include <map>
#include <vector>

namespace cardsApp {
	namespace databasesModule {

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
			std::map<int, sCourseCard*> courses;
			bool load(const rapidjson::Document&);
		};

		class coursesDatabase : public common::databaseModule::databaseInterface {
		public:
			coursesDatabase();
			~coursesDatabase() = default;
			void load(const rapidjson::Document&) override;

		private:
			std::map<int, sCourseBook*> coursesDb;
		};
	}
}


#endif //CARDS_APP_COURSESDATABASE_H
