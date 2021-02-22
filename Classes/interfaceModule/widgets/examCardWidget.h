#ifndef CARDS_APP_EXAMCARDWIDGET_H
#define CARDS_APP_EXAMCARDWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace cardsApp::interfaceModule {

	class examCardWidget : public common::coreModule::nodeProperties<cocos2d::Node> {
	public:
		examCardWidget();
		~examCardWidget() = default;

		CREATE_FUNC(examCardWidget);
	};
}


#endif //CARDS_APP_EXAMCARDWIDGET_H
