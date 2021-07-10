#include "resultCardWidget.h"
#include "buttonIconWidget.h"
#include "common/coreModule/nodes/widgets/gridNode.h"
#include "common/utilityModule/covertUtility.h"
#include "common/utilityModule/stringUtility.h"
#include "databasesModule/coursesTool.h"
#include "databasesModule/databaseManager.h"
#include "databasesModule/ipaDatabase.h"

using namespace cardsApp::interfaceModule;

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
        label->setString(common::utilityModule::capitalizeString(card->enWord));
    }
    if (!card->enDescription.empty()) {
        auto* label = new cocos2d::Label();
        label->setName("labelDescription");
        loadComponent(label);
        label->setString(STRING_FORMAT("(%s)", common::utilityModule::capitalizeString(card->enDescription).c_str()));
        grid->addChild(label);
    }
    if (!card->enSentence.empty()) {
        auto* label = new cocos2d::Label();
        label->setName("label");
        loadComponent(label);
        label->setString(common::utilityModule::capitalizeString(card->enSentence));
        grid->addChild(label);
    }
    grid->updateGridTransform();
}

void resultCardWidget::initSwipeHandle() {
    using namespace cardsApp::databasesModule;
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
            bgWindow->setColor(convertUtility::changeColorFromTo(
                defaultColor, cocos2d::Color3B(235, 87, 87), std::abs(nextPos / xPosLimit)));
        } else {
            bgWindow->setColor(convertUtility::changeColorFromTo(
                defaultColor, cocos2d::Color3B(111, 207, 157), std::abs(nextPos / xPosLimit)));
        }
    };
    listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto nextPos = -(xTouchPos - touch->getLocation().x) / 10;
        auto diffClick = std::abs(xTouchPos) - std::abs(touch->getLocation().x);
        auto hitClick = diffClick > -3 || diffClick < 3;
        if (nextPos > -xPosLimit - 1 && nextPos < xPosLimit - 1) {
            auto rotateAction = cocos2d::RotateTo::create(.1f, 0.f);
            bgWindow->setColor(defaultColor);
            cardHolder->runAction(rotateAction);
            if (hitClick) {
                auto* grid = dynamic_cast<common::coreModule::gridNode*>(findNode("gridContainer"));
                if (grid == nullptr) {
                    return true;
                }
                for (auto node : grid->getChildren()) {
                    auto touchLocation = node->convertToNodeSpace(touch->getLocation());
                    auto rect = cocos2d::Rect(node->getPositionX(),
                                              node->getPositionX(),
                                              node->getContentSize().width,
                                              node->getContentSize().height);
                    if (rect.containsPoint(touchLocation)) {
                        if (auto label = dynamic_cast<cocos2d::Label*>(node)) {
                            auto db = GET_DATABASE_MANAGER().getDatabase<ipaDatabase>(databaseManager::eDatabaseList::IPA_DB);
                            const auto& text = label->getString();
                            const auto& transcript = db->findString(text);
                            std::string temp;
                            // todo create bubble for transcription
                            return true;
                        }
                    }
                }
            }
        } else {
            if (cardSwipeClb) {
                bgWindow->setColor(defaultColor);
                cardSwipeClb(nextPos < -xPosLimit ? eCardSwipeDirection::LEFT : eCardSwipeDirection::RIGHT);
            }
        }
        return true;
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
