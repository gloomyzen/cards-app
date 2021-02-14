#ifndef CARDS_APP_COURSEPREVIEWWINDOW_H
#define CARDS_APP_COURSEPREVIEWWINDOW_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/scenes/windows/windowBase.h"

namespace cardsApp::interfaceModule {

	class coursePreviewWindow : public common::coreModule::windowBase {
	public:
		coursePreviewWindow();
		~coursePreviewWindow();
	};
}//cardsApp::interfaceModule


#endif //CARDS_APP_COURSEPREVIEWWINDOW_H
