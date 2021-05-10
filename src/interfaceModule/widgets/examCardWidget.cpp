#include "examCardWidget.h"
#include "cocos-ext.h"
#include "common/coreModule/nodes/widgets/gridNode.h"
#include "common/utilityModule/stringUtility.h"

using namespace cardsApp::interfaceModule;

examCardWidget::examCardWidget() {
    this->setName("examCardWidget");
    loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
    bgNode = dynamic_cast<cocos2d::ui::Scale9Sprite*>(findNode("cardBg"));
    setOnTouchEnded([this]() {
        if (cardTouchClb)
            cardTouchClb();
    });
}

void examCardWidget::setData(cardsApp::databasesModule::sCourseCard* card) {
    using namespace common::utilityModule;
    auto grid = dynamic_cast<common::coreModule::gridNode*>(findNode("gridContainer"));
    if (auto label = dynamic_cast<cocos2d::Label*>(findNode("firstWord"))) {
        label->setString(stringUtility::capitalizeString(card->ruWord));
    }
    if (!card->ruSentence.empty()) {
        auto label = new cocos2d::Label();
        label->setName("label");
        loadComponent(label);
        label->setString(stringUtility::capitalizeString(card->ruSentence));
        grid->addChild(label);
    }
    grid->updateGridTransform();
}
