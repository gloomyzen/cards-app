//#include "interfaceModule/widgets/testWidget.h"
#include "customNodeTypes.h"
#include "common/coreModule/nodes/nodeFactory.h"
#include "interfaceModule/widgets/cardBtnWidget.h"
#include "interfaceModule/widgets/cardProgressBar.h"
#include "interfaceModule/widgets/cardWidget.h"

using namespace cardsApp::interfaceModule;

void customNodeTypes::registerAllCustomNodes() {
    //	GET_NODE_FACTORY().registerCustomNodeType("testWidget", []() { return new testWidget(); });
    GET_NODE_FACTORY().registerCustomNodeType("cardWidget", []() { return new cardWidget(); });
    GET_NODE_FACTORY().registerCustomNodeType("cardProgressBar", []() { return new cardProgressBar(); });
    GET_NODE_FACTORY().registerCustomNodeType("cardBtnWidget", []() { return new cardBtnWidget(); });
}