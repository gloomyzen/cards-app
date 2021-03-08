#include "resultCardWidget.h"
#include "common/coreModule/nodes/widgets/gridNode.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/covertUtility.h"
#include "common/utilityModule/stringUtility.h"

using namespace cardsApp::interfaceModule;
using namespace common::utilityModule;

resultCardWidget::resultCardWidget() {
    this->setName("resultCardWidget");
    loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
    listener = cocos2d::EventListenerTouchOneByOne::create();
    initSwipeHandle();
}

void resultCardWidget::setData(databasesModule::sCourseCard* card, cocos2d::Node* node, cocos2d::Sprite* sprite) {
    cardHolder = node;
    bgWindow = sprite;
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
        xTouchPos = touch->getLocation().x;
        auto touchLocation = this->convertToNodeSpace(touch->getLocation());
        auto rect = cocos2d::Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
        return rect.containsPoint(touchLocation);
    };
    listener->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        using namespace common::utilityModule;
        auto nextPos = -(xTouchPos - touch->getLocation().x) / 10;
        if (nextPos > -xPosLimit && nextPos < xPosLimit)
            cardHolder->setRotation(nextPos);
        if (nextPos > 0) {
            bgWindow->setColor(convertUtility::changeColor(
                defaultColor, cocos2d::Color3B(235, 87, 87), std::abs(nextPos / xPosLimit)));
            LOG_ERROR(STRING_FORMAT("----- %f, %f", nextPos, nextPos / xPosLimit));
        } else {
            bgWindow->setColor(convertUtility::changeColor(
                defaultColor, cocos2d::Color3B(111, 207, 157), std::abs(nextPos / xPosLimit)));
        }
    };
    listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto nextPos = -(xTouchPos - touch->getLocation().x) / 10;
        LOG_ERROR(STRING_FORMAT("end %f", nextPos));
        if (nextPos > -xPosLimit - 1 && nextPos < xPosLimit - 1) {
            auto rotateAction = cocos2d::RotateTo::create(.1f, 0.f);
            bgWindow->setColor(defaultColor);
            cardHolder->runAction(rotateAction);
        } else {
            if (cardSwipeClb) {
                bgWindow->setColor(defaultColor);
                cardSwipeClb(nextPos < -xPosLimit ? eCardSwipeDirection::LEFT : eCardSwipeDirection::RIGHT);
            }
        }
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
