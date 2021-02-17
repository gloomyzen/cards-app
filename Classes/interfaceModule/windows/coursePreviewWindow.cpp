#include "coursePreviewWindow.h"
#include "common/debugModule/logManager.h"
#include "common/coreModule/nodes/widgets/gridNode.h"

using namespace cardsApp::interfaceModule;
using namespace common::coreModule;

coursePreviewWindow::coursePreviewWindow() {
	this->setName("coursePreviewWindow");
	loadProperty("windows/" + this->getName(), dynamic_cast<Node*>(this));
}

coursePreviewWindow::~coursePreviewWindow() {

}

std::deque<nodeTasks> coursePreviewWindow::getTasks() {
	std::deque<nodeTasks> result;

	result.emplace_back([this]() {
		closeBtn = dynamic_cast<soundButton*>(findNode("closeBtn"));
		if (closeBtn) {
			closeBtn->setOnTouchEnded([this](cocos2d::Touch* touch, cocos2d::Event* event) {
				closeWindow();
			});
		}
		scrollView = dynamic_cast<ui::ScrollView*>(findNode("scrollContainer"));

		return eTasksStatus::STATUS_OK;
	});

	result.emplace_back([this]() {
		auto cards = getData("cards", std::map<int, cardsApp::databasesModule::sCourseCard*>());
		showList(cards);

		return eTasksStatus::STATUS_OK;
	});

	return result;
}

void coursePreviewWindow::showList(std::map<int, cardsApp::databasesModule::sCourseCard *>) {
	if (!scrollView)
		return;
	auto grid = new gridNode();
	grid->setName("grid");
	loadComponent("windows/" + this->getName(), grid);
	scrollView->addChild(grid);
}