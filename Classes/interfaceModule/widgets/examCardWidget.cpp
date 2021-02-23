#include "examCardWidget.h"

using namespace cardsApp::interfaceModule;

examCardWidget::examCardWidget() {
	this->setName("examCardWidget");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
}

void examCardWidget::setData(int, cardsApp::databasesModule::sCourseCard* card) {

}
