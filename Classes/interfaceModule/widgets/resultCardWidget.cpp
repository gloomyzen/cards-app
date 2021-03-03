#include "resultCardWidget.h"
#include "common/utilityModule/stringUtility.h"
#include "common/coreModule/nodes/widgets/gridNode.h"

using namespace cardsApp::interfaceModule;

resultCardWidget::resultCardWidget() {
	this->setName("resultCardWidget");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node *>(this));
}

void resultCardWidget::setData(cardsApp::databasesModule::sCourseCard* card) {
	using namespace common::utilityModule;
	auto grid = dynamic_cast<common::coreModule::gridNode *>(findNode("gridContainer"));
	if (auto label = dynamic_cast<cocos2d::Label *>(findNode("firstWord"))) {
		label->setString(stringUtility::capitalizeString(card->enWord, stringUtility::eLocaleType::EN));
	}
	if (!card->enDescription.empty()) {
		auto label = new cocos2d::Label();
		label->setName("labelDescription");
		loadComponent("widgets/" + this->getName(), label);
		label->setString(stringUtility::capitalizeString(card->enDescription, stringUtility::eLocaleType::EN));
		grid->addChild(label);
	}
	if (!card->enSentence.empty()) {
		auto label = new cocos2d::Label();
		label->setName("label");
		loadComponent("widgets/" + this->getName(), label);
		label->setString(stringUtility::capitalizeString(card->enSentence, stringUtility::eLocaleType::EN));
		grid->addChild(label);
	}
	grid->updateGridTransform();
}
