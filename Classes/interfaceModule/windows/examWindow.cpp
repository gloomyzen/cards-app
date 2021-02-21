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
		//
		return eTasksStatus::STATUS_OK;
	});

	return result;
}
