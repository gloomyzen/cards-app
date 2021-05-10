#ifndef CARDS_APP_CARDPROGRESSBAR_H
#define CARDS_APP_CARDPROGRESSBAR_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "ui/CocosGUI.h"

namespace cardsApp::interfaceModule {

    class cardProgressBar
        : public common::coreModule::nodeProperties
        , public cocos2d::Node {
      public:
        cardProgressBar();
        ~cardProgressBar() = default;

        CREATE_FUNC(cardProgressBar);

        void setProgress(int i = 0);

      protected:
        cocos2d::ui::Scale9Sprite* progressBar = nullptr;

        cocos2d::Size progressBarSize;
    };
}// namespace cardsApp::interfaceModule


#endif// CARDS_APP_CARDPROGRESSBAR_H
