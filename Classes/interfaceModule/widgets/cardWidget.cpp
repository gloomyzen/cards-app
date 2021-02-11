#include "cardWidget.h"

using namespace cardsApp::interfaceModule;

cardWidget::cardWidget() {
	this->setName("cardWidget");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
	progressBar = dynamic_cast<cardProgressBar*>(findNode("cardProgressBar"));
}

void cardWidget::initCard(std::pair<int, cardsApp::databasesModule::sCourseBook*> pair) {
	if (auto label = dynamic_cast<cocos2d::Label*>(findNode("progressLabel"))) {
		label->setString(STRING_FORMAT("%d", pair.first) + "%");
		progressBar->setProgress(pair.first);
	}
	if (auto label = dynamic_cast<cocos2d::Label*>(findNode("nameLabel"))) {
		label->setString(STRING_FORMAT("1-%d", static_cast<int>(pair.second->cards.size())));
	}
	if (auto label = dynamic_cast<cocos2d::Label*>(findNode("countCardsLabel"))) {
		label->setString(pair.second->name);
	}
}
