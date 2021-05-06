//#include "interfaceModule/widgets/testWidget.h"
#include "customNodeTypes.h"
#include "common/coreModule/nodes/nodeFactory.h"
#include "interfaceModule/widgets/cardBtnWidget.h"
#include "interfaceModule/widgets/cardProgressBar.h"
#include "interfaceModule/widgets/cardWidget.h"
#include "interfaceModule/widgets/closeBtnWidget.h"

// all windows
#include "interfaceModule/windows/coursePreviewWindow.h"
#include "interfaceModule/windows/examWindow.h"
#include "interfaceModule/windows/notifyWindow.h"

using namespace cardsApp::interfaceModule;

void customNodeTypes::registerAllCustomNodes() {
    //	GET_NODE_FACTORY().registerCustomNodeType("testWidget", []() { return new testWidget(); });
    GET_NODE_FACTORY().registerCustomNodeType("cardWidget", []() { return new cardWidget(); });
    GET_NODE_FACTORY().registerCustomNodeType("cardProgressBar", []() { return new cardProgressBar(); });
    GET_NODE_FACTORY().registerCustomNodeType("cardBtnWidget", []() { return new cardBtnWidget(); });
    GET_NODE_FACTORY().registerCustomNodeType("closeBtnWidget", []() { return new closeBtnWidget(); });

    // register all windows
    GET_GAME_MANAGER().registerWindow("coursePreviewWindow", []() { return new coursePreviewWindow(); });
    GET_GAME_MANAGER().registerWindow("examWindow", []() { return new examWindow(); });
    GET_GAME_MANAGER().registerWindow("notifyWindow", []() { return new notifyWindow(); });
}
