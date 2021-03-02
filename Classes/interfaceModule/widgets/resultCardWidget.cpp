#include "resultCardWidget.h"

using namespace cardsApp::interfaceModule;

resultCardWidget::resultCardWidget() {
	this->setName("resultCardWidget");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node *>(this));
}
