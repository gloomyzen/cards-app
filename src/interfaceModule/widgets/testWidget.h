#ifndef CARDS_APP_TESTWIDGET_H
#define CARDS_APP_TESTWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace cardsApp::interfaceModule {

    class testWidget
        : public common::coreModule::nodeProperties
        , public cocos2d::Node {
      public:
        testWidget();
        ~testWidget() = default;

        bool init() {
            if (!Node::init()) {
                return false;
            }
            return true;
        }

        void someMethod() {}
    };
}// namespace cardsApp::interfaceModule


#endif// CARDS_APP_TESTWIDGET_H
