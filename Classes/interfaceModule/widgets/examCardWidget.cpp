#include "examCardWidget.h"
#include "common/coreModule/nodes/widgets/gridNode.h"
#include "cocos-ext.h"
#include "common/utilityModule/stringUtility.h"

using namespace cardsApp::interfaceModule;

examCardWidget::examCardWidget() {
	this->setName("examCardWidget");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node *>(this));
	bgNode = dynamic_cast<cocos2d::ui::Scale9Sprite *>(findNode("cardBg"));
	setOnTouchBegan([this](cocos2d::Touch *touch, cocos2d::Event *event) {
		if (cardTouchClb)
			cardTouchClb();
	});
}

void examCardWidget::setData(int, cardsApp::databasesModule::sCourseCard *card) {
	using namespace common::utilityModule;
	auto grid = dynamic_cast<common::coreModule::gridNode *>(findNode("gridContainer"));
	if (auto label = dynamic_cast<cocos2d::Label *>(findNode("firstWord"))) {
		label->setString(stringUtility::capitalizeString(card->ruWord, stringUtility::eLocaleType::RU));
	}
	if (!card->ruSentence.empty()) {
		auto label = new cocos2d::Label();
		label->setName("label");
		loadComponent("widgets/" + this->getName(), label);
		label->setString(stringUtility::capitalizeString(card->ruSentence, stringUtility::eLocaleType::RU));
		grid->addChild(label);
	}
	grid->updateGridTransform();
}
