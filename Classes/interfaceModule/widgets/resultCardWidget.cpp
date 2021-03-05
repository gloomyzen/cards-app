#include "resultCardWidget.h"
#include "common/coreModule/nodes/widgets/gridNode.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/stringUtility.h"

using namespace cardsApp::interfaceModule;
using namespace common::utilityModule;

resultCardWidget::resultCardWidget() {
    this->setName("resultCardWidget");
    loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
    listener = cocos2d::EventListenerTouchOneByOne::create();
    initSwipeHandle();
}

void resultCardWidget::setData(cardsApp::databasesModule::sCourseCard* card) {
    auto* grid = dynamic_cast<common::coreModule::gridNode*>(findNode("gridContainer"));
    if (auto* label = dynamic_cast<cocos2d::Label*>(findNode("firstWord"))) {
        label->setString(stringUtility::capitalizeString(card->enWord));
    }
    if (!card->enDescription.empty()) {
        auto* label = new cocos2d::Label();
        label->setName("labelDescription");
        loadComponent("widgets/" + this->getName(), label);
        label->setString(STRING_FORMAT("(%s)", stringUtility::capitalizeString(card->enDescription).c_str()));
        grid->addChild(label);
    }
    if (!card->enSentence.empty()) {
        auto* label = new cocos2d::Label();
        label->setName("label");
        loadComponent("widgets/" + this->getName(), label);
        label->setString(stringUtility::capitalizeString(card->enSentence));
        grid->addChild(label);
    }
    grid->updateGridTransform();
}

void resultCardWidget::initSwipeHandle() {
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        xTouchPos = 0.f;
        auto touchLocation = this->convertToNodeSpace(touch->getLocation());
        auto rect = cocos2d::Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
        return rect.containsPoint(touchLocation);
    };
    listener->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        LOG_ERROR(STRING_FORMAT("move %f %f", touch->getLocation().x, touch->getLocation().y));
    };
    listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        LOG_ERROR(STRING_FORMAT("end %f %f", touch->getLocation().x, touch->getLocation().y));
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
