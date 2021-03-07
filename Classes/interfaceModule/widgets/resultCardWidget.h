#ifndef CARDS_APP_RESULTCARDWIDGET_H
#define CARDS_APP_RESULTCARDWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "databasesModule/coursesDatabase.h"

namespace cardsApp::interfaceModule {

    class resultCardWidget : public common::coreModule::nodeProperties<cocos2d::Node> {
      public:
        enum class eCardSwipeDirection {
            LEFT = 0,
            RIGHT,
        };
        resultCardWidget();
        ~resultCardWidget() = default;
        CREATE_FUNC(resultCardWidget);

        void setData(databasesModule::sCourseCard*, cocos2d::Node*, cocos2d::Sprite*);
        void setSwipeClb(std::function<void(eCardSwipeDirection)> clb) { cardSwipeClb = std::move(clb); }

      private:
        void initSwipeHandle();

        std::function<void(eCardSwipeDirection)> cardSwipeClb = nullptr;
        cocos2d::EventListenerTouchOneByOne* listener = nullptr;
        cocos2d::Node* cardHolder = nullptr;
        cocos2d::Sprite* bgWindow = nullptr;
        float xTouchPos = 0.f;
        float xPosLimit = 7.f;
    };
}// namespace cardsApp::interfaceModule


#endif// CARDS_APP_RESULTCARDWIDGET_H
