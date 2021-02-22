#include "examWindow.h"

using namespace cardsApp::interfaceModule;

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
		auto cardsId = getData("cardsId", 0);
//		if (cardsId) {
//			initCard(cardsId);
//		}

		return eTasksStatus::STATUS_OK;
	});

	return result;
}
