#ifndef CARDS_APP_CARDBTNWIDGET_H
#define CARDS_APP_CARDBTNWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/widgets/soundButton.h"

namespace cardsApp::interfaceModule {

    class cardBtnWidget : public common::coreModule::soundButton {
      public:
        cardBtnWidget();
        ~cardBtnWidget() override = default;

        CREATE_FUNC(cardBtnWidget);

        void setText(const std::string&);

      private:
        cocos2d::Label* label = nullptr;
    };
}// namespace cardsApp::interfaceModule

#endif// CARDS_APP_CARDBTNWIDGET_H
