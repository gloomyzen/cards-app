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
        enum class eButtonIcon {
            NONE = 0,
            CLOSE,
            RECYCLE,
            RETURN
        };
        enum class eButtonBgColor {
            WHITE = 0,
            WHITE_BORDER,
            RED
        };

        buttonIconWidget();
        ~buttonIconWidget() override = default;

        std::deque<nodeTasks> getTasks() override;

        void buttonClickClb(const std::function<void()> &clb);

        void setIcon(eButtonIcon);

    private:
        void setBgColor(eButtonBgColor);
        std::function<void()> closeClb = nullptr;
    };
}// namespace cardsApp::interfaceModule


#endif// CARDS_APP_BUTTONICONWIDGET_H
