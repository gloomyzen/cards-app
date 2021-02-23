#include "examCardWidget.h"
#include "common/coreModule/nodes/widgets/gridNode.h"

using namespace cardsApp::interfaceModule;

examCardWidget::examCardWidget() {
	this->setName("examCardWidget");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
}

void examCardWidget::setData(int, cardsApp::databasesModule::sCourseCard* card) {
	auto grid = dynamic_cast<common::coreModule::gridNode*>(findNode("gridContainer"));
	grid->updateGridTransform();
}
