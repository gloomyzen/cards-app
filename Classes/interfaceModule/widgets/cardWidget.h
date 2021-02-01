#ifndef CARDS_APP_CARDWIDGET_H
#define CARDS_APP_CARDWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace cardsApp::interfaceModule {

	class cardWidget : public common::coreModule::nodeProperties<cocos2d::Node> {
	public:
		cardWidget();
		~cardWidget() = default;

		CREATE_FUNC(cardWidget);

		static Node *createNode() {
			return cardWidget::create();
		}
	};
}//cardsApp::interfaceModule

#endif //CARDS_APP_CARDWIDGET_H
