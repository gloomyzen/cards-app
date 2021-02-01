#include "cardWidget.h"

using namespace cardsApp::interfaceModule;

cardWidget::cardWidget() {
	this->setName("cardWidget");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
}
