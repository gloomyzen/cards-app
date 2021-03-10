#ifndef CARDS_APP_CLOSEBTNWIDGET_H
#define CARDS_APP_CLOSEBTNWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/widgets/soundButton.h"
#include <functional>
#include <utility>

namespace cardsApp::interfaceModule {

    class closeBtnWidget
        : public common::coreModule::soundButton
        , public taskHolder {
      public:
        closeBtnWidget();
        ~closeBtnWidget() = default;

        CREATE_FUNC(closeBtnWidget);
        std::deque<nodeTasks> getTasks() override;

        void setCloseClb(std::function<void()> clb) { closeClb = clb; }

      private:
        std::function<void()> closeClb = nullptr;
    };
}// namespace cardsApp::interfaceModule


#endif// CARDS_APP_CLOSEBTNWIDGET_H
