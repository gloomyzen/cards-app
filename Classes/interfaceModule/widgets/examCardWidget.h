#ifndef CARDS_APP_EXAMCARDWIDGET_H
#define CARDS_APP_EXAMCARDWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "databasesModule/coursesDatabase.h"
#include "common/coreModule/nodes/widgets/soundButton.h"
#include <functional>
#include <utility>

namespace cardsApp::interfaceModule {

	class examCardWidget : public common::coreModule::soundButton {
	public:
		examCardWidget();
		~examCardWidget() = default;

		CREATE_FUNC(examCardWidget);

		void setData(int, databasesModule::sCourseCard*);
		void setTouchClb(std::function<void()> clb) { cardTouchClb = std::move(clb); }

	private:
		std::function<void()> cardTouchClb = nullptr;
	};
}


#endif //CARDS_APP_EXAMCARDWIDGET_H
