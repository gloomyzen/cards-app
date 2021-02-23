#ifndef CARDS_APP_EXAMWINDOW_H
#define CARDS_APP_EXAMWINDOW_H

#include "cocos2d.h"
#include "common/coreModule/scenes/windows/windowBase.h"
#include "databasesModule/coursesDatabase.h"

namespace cardsApp::interfaceModule {

	class examWindow : public common::coreModule::windowBase, public taskHolder {
	public:
		examWindow();
		~examWindow();
		std::deque<nodeTasks> getTasks() override;

	private:
		void initExam(int id);
		void goToNextCard();

		std::vector<std::pair<int, databasesModule::sCourseCard*>> currentCards;
	};
}


#endif //CARDS_APP_EXAMWINDOW_H
