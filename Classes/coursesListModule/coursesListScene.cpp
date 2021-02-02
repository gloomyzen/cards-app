#include "coursesListScene.h"
#include "databasesModule/coursesTool.h"
#include "interfaceModule/widgets/cardWidget.h"

using namespace cardsApp::coursesListModule;
using namespace cardsApp::interfaceModule;
using namespace cocos2d;

coursesListScene::coursesListScene() {
	this->setName("coursesListScene");
	loadProperty(STRING_FORMAT("coursesListScene/%s", this->getName().c_str()), this);
}

coursesListScene::~coursesListScene() {}

std::deque<nodeTasks> coursesListScene::getTasks() {
	std::deque<nodeTasks> result;
	result.emplace_back([this]() {
		scrollView = dynamic_cast<ui::ScrollView*>(findNode("scrollContainer"));

		return eTasksStatus::STATUS_OK;
	});

	result.emplace_back([this]() {
		//todo remove after testing
		databasesModule::coursesTool tool;
		auto list = tool.getCoursesWithProgress();
//		for (auto item : list) {
//			auto card = new cardWidget();
//			scrollView->addChild(card);
//		}
//		auto liquid = Liquid::create(5.0, {32, 24}, 5, 8);
//		grid->runAction(liquid);
//		auto gridProp = grid->getGrid();
//		auto liquidAction = Liquid::create(10, cocos2d::Size(10, 10), 2, 5);
//		grid->runAction(liquidAction);

		return eTasksStatus::STATUS_OK;
	});

	return result;
}
