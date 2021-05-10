#ifndef CARDS_APP_LOCALPROFILEBLOCK_H
#define CARDS_APP_LOCALPROFILEBLOCK_H

#include "common/profileModule/profileBlockInterface.h"
#include "rapidjson/document.h"
#include "rapidjson/ostreamwrapper.h"
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace cardsApp::localProfile {

        struct sLocalProfileCourse {
            int id;
            std::vector<int> goodQuestion;
            std::vector<int> mediumQuestion;
            std::vector<int> badQuestion;

            bool load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject&);
            bool save(rapidjson::Value&, rapidjson::Document::AllocatorType&);
            void updateAnswers(int cardId, bool answerId);
        };

        class localProfileBlock : public common::profileModule::profileBlockInterface {
          public:
            localProfileBlock();
            ~localProfileBlock();

            bool load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject&) override;
            bool save(rapidjson::Value&, rapidjson::Document::AllocatorType&) override;

            std::map<int, sLocalProfileCourse*>& getAllCourses() { return localCourses; }

            sLocalProfileCourse* getCourse(int);
            void resetCourseProgress(int courseId);


          private:
            std::map<int, sLocalProfileCourse*> localCourses;
        };
    }// namespace cardsApp


#endif// CARDS_APP_LOCALPROFILEBLOCK_H
