#ifndef CARDS_APP_BUTTONICONWIDGET_H
#define CARDS_APP_BUTTONICONWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/widgets/soundButton.h"
#include <functional>
#include <utility>

namespace cardsApp::interfaceModule {

    class buttonIconWidget
        : public common::coreModule::soundButton
        , public taskHolder {
    public:
        buttonIconWidget();
        ~buttonIconWidget() override = default;

        std::deque<nodeTasks> getTasks() override;

        void buttonClickClb(std::function<void()> clb) {
            closeClb = std::move(clb);
        }

    private:
        std::function<void()> closeClb = nullptr;
    };
}// namespace cardsApp::interfaceModule


#endif// CARDS_APP_BUTTONICONWIDGET_H
