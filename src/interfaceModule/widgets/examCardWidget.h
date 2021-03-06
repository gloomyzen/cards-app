#ifndef CARDS_APP_EXAMCARDWIDGET_H
#define CARDS_APP_EXAMCARDWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/widgets/soundButton.h"
#include "databasesModule/coursesDatabase.h"
#include <functional>
#include <utility>

namespace cardsApp::interfaceModule {

    class examCardWidget : public common::coreModule::soundButton {
      public:
        examCardWidget();
        ~examCardWidget() = default;

        void setData(databasesModule::sCourseCard*);
        void setTouchClb(std::function<void()> clb) { cardTouchClb = clb; }

      private:
        std::function<void()> cardTouchClb = nullptr;
    };
}// namespace cardsApp::interfaceModule


#endif// CARDS_APP_EXAMCARDWIDGET_H
