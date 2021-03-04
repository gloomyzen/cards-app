#ifndef CARDS_APP_RESULTCARDWIDGET_H
#define CARDS_APP_RESULTCARDWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "databasesModule/coursesDatabase.h"

namespace cardsApp::interfaceModule {

	class resultCardWidget : public common::coreModule::nodeProperties<cocos2d::Node> {
	public:
		enum class eCardSwipeDirection {
			LEFT = 0,
			RIGHT,
			};
		resultCardWidget();
		~resultCardWidget() = default;
		CREATE_FUNC(resultCardWidget);

		void setData(databasesModule::sCourseCard*);
		void setSwipeClb(std::function<void(eCardSwipeDirection)> clb) { cardSwipeClb = std::move(clb); }

	private:
		void initSwipeHandle();

		std::function<void(eCardSwipeDirection)> cardSwipeClb = nullptr;
		cocos2d::EventListenerTouchOneByOne* listener = nullptr;
		float xTouchPos = 0.f;
	};
}


#endif //CARDS_APP_RESULTCARDWIDGET_H
