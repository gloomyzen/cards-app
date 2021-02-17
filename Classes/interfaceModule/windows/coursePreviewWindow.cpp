#include "coursePreviewWindow.h"
#include "common/debugModule/logManager.h"

using namespace cardsApp::interfaceModule;

coursePreviewWindow::coursePreviewWindow() {
	this->setName("coursePreviewWindow");
	loadProperty("windows/" + this->getName(), dynamic_cast<Node*>(this));
}

coursePreviewWindow::~coursePreviewWindow() {

}

std::deque<nodeTasks> coursePreviewWindow::getTasks() {
	std::deque<nodeTasks> result;
	result.emplace_back([this]() {
		auto cards = getData("cards", std::map<int, cardsApp::databasesModule::sCourseCard*>());
		showList(cards);

		return eTasksStatus::STATUS_OK;
	});

	return result;
}

void coursePreviewWindow::showList(std::map<int, cardsApp::databasesModule::sCourseCard *>) {
	//
}