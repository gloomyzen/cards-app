#ifndef CARDS_APP_RESULTCARDWIDGET_H
#define CARDS_APP_RESULTCARDWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "databasesModule/coursesDatabase.h"
#include "common/coreModule/nodes/widgets/soundButton.h"
#include <functional>
#include <utility>

namespace cardsApp::interfaceModule {

	class resultCardWidget : public common::coreModule::soundButton {
	public:
		resultCardWidget();
		~resultCardWidget() = default;
		CREATE_FUNC(resultCardWidget);
	};
}


#endif //CARDS_APP_RESULTCARDWIDGET_H
