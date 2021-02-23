#include "examWindow.h"

#include "common/databaseModule/databaseInterface.h"
#include "common/databaseModule/databaseManager.h"
#include "databasesModule/coursesDatabase.h"
#include <tuple>

using namespace cardsApp::interfaceModule;
using namespace cocos2d;
using namespace common::coreModule;

examWindow::examWindow() {
	this->setName("examWindow");
	loadProperty("windows/" + this->getName(), dynamic_cast<Node*>(this));
	setHandleMissClick(false);
}

examWindow::~examWindow() {

}

std::deque<nodeTasks> examWindow::getTasks() {
	std::deque<nodeTasks> result;

	result.emplace_back([this]() {
		auto closeBtn = dynamic_cast<soundButton*>(findNode("closeBtn"));
		if (closeBtn) {
			closeBtn->setOnTouchEnded([this](cocos2d::Touch* touch, cocos2d::Event* event) {
				closeWindow();
			});
		}

		return eTasksStatus::STATUS_OK;
	});

	result.emplace_back([this]() {
		auto courseName = getData("courseName", std::string());
		if (!courseName.empty()) {
			if (auto label = dynamic_cast<Label*>(findNode("windowTitle"))) {
				label->setString(courseName);
			}
		}
		auto cardsId = getData("cardsId", 0);
		if (cardsId) {
			initExam(cardsId);
			goToNextCard();
		}


		return eTasksStatus::STATUS_OK;
	});

	return result;
}

void examWindow::initExam(int id) {
	auto coursesDb = GET_DATABASE_MANAGER().getDatabase<databasesModule::coursesDatabase>("coursesDb");
	auto cards = coursesDb->getCourseById(id);
	std::for_each(cards->cards.begin(), cards->cards.end(), [&](std::pair<int, databasesModule::sCourseCard*> e){
		currentCards.push_back(e);
	});
	auto rd = std::random_device {};
	auto rng = std::default_random_engine { rd() };
	std::shuffle(std::begin(currentCards), std::end(currentCards), rng);
}

void examWindow::goToNextCard() {
	if (currentCards.empty()) {
		//todo go to result window
	}
	auto cardHolder = findNode("cardHolder");

}
