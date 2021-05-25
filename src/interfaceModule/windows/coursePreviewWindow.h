#ifndef CARDS_APP_COURSEPREVIEWWINDOW_H
#define CARDS_APP_COURSEPREVIEWWINDOW_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/widgets/soundButton.h"
#include "common/coreModule/scenes/windows/windowBase.h"
#include "databasesModule/coursesDatabase.h"
#include "ui/CocosGUI.h"
#include <map>

namespace cardsApp::interfaceModule {

    class coursePreviewWindow
        : public common::coreModule::windowBase
        , public taskHolder {
    public:
        coursePreviewWindow();
        ~coursePreviewWindow();
        std::deque<nodeTasks> getTasks() override;

    private:
        void showList(int, const std::string&);
    };
}// namespace cardsApp::interfaceModule


#endif// CARDS_APP_COURSEPREVIEWWINDOW_H
