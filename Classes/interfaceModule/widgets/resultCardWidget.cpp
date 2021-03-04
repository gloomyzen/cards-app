#include "resultCardWidget.h"
#include "common/utilityModule/stringUtility.h"
#include "common/coreModule/nodes/widgets/gridNode.h"
#include "common/debugModule/logManager.h"

using namespace cardsApp::interfaceModule;
using namespace cocos2d::network;
using namespace common::utilityModule;

resultCardWidget::resultCardWidget() {
	this->setName("resultCardWidget");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node *>(this));
}

void resultCardWidget::setData(cardsApp::databasesModule::sCourseCard* card) {
	auto grid = dynamic_cast<common::coreModule::gridNode *>(findNode("gridContainer"));
	if (auto label = dynamic_cast<cocos2d::Label *>(findNode("firstWord"))) {
		label->setString(stringUtility::capitalizeString(card->enWord));
	}
	if (!card->enDescription.empty()) {
		auto label = new cocos2d::Label();
		label->setName("labelDescription");
		loadComponent("widgets/" + this->getName(), label);
		label->setString(STRING_FORMAT("(%s)", stringUtility::capitalizeString(card->enDescription).c_str()));
		grid->addChild(label);
	}
	if (!card->enSentence.empty()) {
		auto label = new cocos2d::Label();
		label->setName("label");
		loadComponent("widgets/" + this->getName(), label);
		label->setString(stringUtility::capitalizeString(card->enSentence));
		grid->addChild(label);
	}
	grid->updateGridTransform();
}