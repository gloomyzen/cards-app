#ifndef CARDS_APP_NOTIFYWINDOW_H
#define CARDS_APP_NOTIFYWINDOW_H

#include "cocos2d.h"
#include "common/coreModule/scenes/windows/windowBase.h"
#include "databasesModule/coursesDatabase.h"

namespace cardsApp::interfaceModule {

    class notifyWindow
        : public common::coreModule::windowBase
        , public taskHolder {
    public:
        notifyWindow();
        ~notifyWindow() = default;
        std::deque<nodeTasks> getTasks() override;
    };
}// namespace cardsApp::interfaceModule


#endif// CARDS_APP_NOTIFYWINDOW_H
