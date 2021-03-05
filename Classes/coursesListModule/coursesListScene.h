#ifndef CARDS_APP_COURSESLISTSCENE_H
#define CARDS_APP_COURSESLISTSCENE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "ui/CocosGUI.h"
#include <vector>

namespace cardsApp {
    namespace coursesListModule {

        class coursesListScene
            : public common::coreModule::nodeProperties<cocos2d::Node>
            , public taskHolder {
          public:
            coursesListScene();
            ~coursesListScene();
            CREATE_FUNC(coursesListScene);
            std::deque<nodeTasks> getTasks() override;

          private:
            cocos2d::ui::ScrollView* scrollView = nullptr;
        };
    }// namespace coursesListModule
}// namespace cardsApp


#endif// CARDS_APP_COURSESLISTSCENE_H
