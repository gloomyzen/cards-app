#include "coursePreviewWindow.h"
#include "common/debugModule/logManager.h"
#include "common/coreModule/nodes/widgets/gridNode.h"

#include "common/databaseModule/databaseInterface.h"
#include "common/databaseModule/databaseManager.h"
#include "databasesModule/coursesDatabase.h"

using namespace cardsApp::interfaceModule;
using namespace common::coreModule;

coursePreviewWindow::coursePreviewWindow() {
	this->setName("coursePreviewWindow");
	loadProperty("windows/" + this->getName(), dynamic_cast<Node*>(this));
	setHandleMissClick(false);
}

coursePreviewWindow::~coursePreviewWindow() {

}

std::deque<nodeTasks> coursePreviewWindow::getTasks() {
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
		if (cardsId) {
			showList(cardsId);
		}
		auto courseName = getData("courseName", std::string());
		if (!courseName.empty()) {
			if (auto label = dynamic_cast<Label*>(findNode("windowTitle"))) {
				label->setString(courseName);
			}
		}

		return eTasksStatus::STATUS_OK;
	});

	return result;
}

void coursePreviewWindow::showList(int cardsId) {
	auto scrollView = dynamic_cast<ui::ScrollView*>(findNode("scrollContainer"));
	if (!scrollView) {
		return;
	}
	auto coursesDb = GET_DATABASE_MANAGER().getDatabase<databasesModule::coursesDatabase>("coursesDb");
	auto cards = coursesDb->getCourseById(cardsId);
	auto grid = new gridNode();
	grid->setName("grid");
	loadComponent("windows/" + this->getName(), grid);
	scrollView->addChild(grid);
	int cntWords = cards->cards.size();
	for (auto item : cards->cards) {
		auto label = new Label();
		label->setName("label");
		loadComponent("windows/" + this->getName(), label);
		grid->addChild(label);
		label->setString(STRING_FORMAT("%d. %s", cntWords--, item.second->enWord.c_str()));
	}
	grid->updateGridTransform();
	scrollView->setInnerContainerSize( grid->getContentSize() );
	if (scrollView->getContentSize().height < grid->getContentSize().height) {
		scrollView->setScrollBarEnabled(true);
		scrollView->setScrollBarColor(cocos2d::Color3B(255, 255, 255));
		scrollView->setScrollBarAutoHideEnabled(false);
	}
	if (auto btn = dynamic_cast<soundButton*>(findNode("btn"))) {
		btn->setOnTouchEnded([](cocos2d::Touch* touch, cocos2d::Event* event) {
			if (auto window = GET_GAME_MANAGER().requestWindow("examWindow", true)) {
//				window->setData()
			}
		});
	}
}