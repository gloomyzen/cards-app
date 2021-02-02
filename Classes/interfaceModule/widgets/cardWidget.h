#ifndef CARDS_APP_CARDWIDGET_H
#define CARDS_APP_CARDWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace cardsApp::interfaceModule {

	class cardWidget : public common::coreModule::nodeProperties<cocos2d::Sprite> {
	public:
		cardWidget();
		~cardWidget() = default;

		CREATE_FUNC(cardWidget);
	};
}//cardsApp::interfaceModule

#endif //CARDS_APP_CARDWIDGET_H
