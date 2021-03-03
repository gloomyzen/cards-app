#ifndef CARDS_APP_RESULTCARDWIDGET_H
#define CARDS_APP_RESULTCARDWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "databasesModule/coursesDatabase.h"
#include "cocos/network/HttpClient.h"

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
		void sendRequest(const std::string& name);
		void insertImage(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

		std::function<void(eCardSwipeDirection)> cardSwipeClb = nullptr;
	};
}


#endif //CARDS_APP_RESULTCARDWIDGET_H
