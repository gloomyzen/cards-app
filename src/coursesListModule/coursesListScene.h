#ifndef CARDS_APP_COURSESLISTSCENE_H
#define CARDS_APP_COURSESLISTSCENE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "ui/CocosGUI.h"
#include <vector>

namespace cardsApp {
    namespace coursesListModule {

        class coursesListScene
            : public common::coreModule::nodeProperties
            , public cocos2d::Layer
            , public taskHolder {
          public:
            coursesListScene();
            ~coursesListScene();
            std::deque<nodeTasks> getTasks() override;

          private:
            cocos2d::ui::ScrollView* scrollView = nullptr;
        };
    }// namespace coursesListModule
}// namespace cardsApp


#endif// CARDS_APP_COURSESLISTSCENE_H
