#ifndef CARDS_APP_TESTWIDGET_H
#define CARDS_APP_TESTWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace cardsApp::interfaceModule {

	class testWidget : public common::coreModule::nodeProperties<cocos2d::Node> {
		public:
			testWidget();
			~testWidget() = default;

			CREATE_FUNC(testWidget);

			static Node *createNode() {
				return testWidget::create();
			}

			bool init() {
				if (!Node::init()) {
					return false;
				}
				return true;
			}

			void someMethod(){}

		};
	}//cardsApp::interfaceModule


#endif //CARDS_APP_TESTWIDGET_H
