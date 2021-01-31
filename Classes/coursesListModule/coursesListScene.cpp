#include "coursesListScene.h"

using namespace cardsApp::coursesListModule;
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

	return result;
}
