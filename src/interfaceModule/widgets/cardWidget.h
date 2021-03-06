#ifndef CARDS_APP_CARDWIDGET_H
#define CARDS_APP_CARDWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/widgets/soundButton.h"
#include "databasesModule/coursesDatabase.h"
#include "interfaceModule/widgets/cardProgressBar.h"
#include <tuple>

namespace cardsApp::interfaceModule {

    class cardWidget : public common::coreModule::soundButton {
      public:
        cardWidget();
        ~cardWidget() = default;

        void initCard(std::pair<int, cardsApp::databasesModule::sCourseBook*>);

      protected:
        cardProgressBar* progressBar = nullptr;
    };
}// namespace cardsApp::interfaceModule

#endif// CARDS_APP_CARDWIDGET_H
