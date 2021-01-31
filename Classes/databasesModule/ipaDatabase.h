#ifndef CARDS_APP_IPADATABASE_H
#define CARDS_APP_IPADATABASE_H

#include "common/databaseModule/databaseInterface.h"
#include "cocos2d.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <string>
#include <map>
#include <vector>

namespace cardsApp {
	namespace databasesModule {

		typedef std::map<std::string, std::string> sLetter;

		class ipaDatabase : public common::databaseModule::databaseInterface {
		public:
			ipaDatabase();
			~ipaDatabase() = default;
			void load(const rapidjson::Document&) override;

			bool loadDictionary(const std::string&, const rapidjson::Document&);

		private:
			std::map<std::string, sLetter> stringMapDb;

		};
	}
}


#endif //CARDS_APP_IPADATABASE_H
