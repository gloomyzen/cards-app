#include "examWindow.h"

#include "common/databaseModule/databaseInterface.h"
#include "common/databaseModule/databaseManager.h"
#include "databasesModule/coursesDatabase.h"
#include "interfaceModule/widgets/examCardWidget.h"
#include "interfaceModule/widgets/resultCardWidget.h"
#include <tuple>

using namespace cardsApp::interfaceModule;
using namespace cocos2d;
using namespace common::coreModule;

examWindow::examWindow() {
    this->setName("examWindow");
    loadProperty("windows/" + this->getName(), dynamic_cast<Node*>(this));
    setHandleMissClick(false);
}

examWindow::~examWindow() {}

std::deque<nodeTasks> examWindow::getTasks() {
    std::deque<nodeTasks> result;

    result.emplace_back([this]() {
        auto closeBtn = dynamic_cast<soundButton*>(findNode("closeBtn"));
        if (closeBtn) {
            closeBtn->setOnTouchEnded([this](cocos2d::Touch* touch, cocos2d::Event* event) { closeWindow(); });
        }

        return eTasksStatus::STATUS_OK;
    });

    result.emplace_back([this]() {
        auto bg = findNode("bg");
        bgColor = bg->getColor();

        return eTasksStatus::STATUS_OK;
    });

    result.emplace_back([this]() {
        auto courseName = getData("courseName", std::string());
        if (!courseName.empty()) {
            if (auto label = dynamic_cast<Label*>(findNode("windowTitle"))) {
                label->setString(courseName);
            }
        }
        auto cardsId = getData("cardsId", 0);
        if (cardsId) {
            initExam(cardsId);
            goToNextCard();
        }

        return eTasksStatus::STATUS_OK;
    });

    return result;
}

void examWindow::initExam(int id) {
    auto coursesDb = GET_DATABASE_MANAGER().getDatabase<databasesModule::coursesDatabase>("coursesDb");
    auto cards = coursesDb->getCourseById(id);
    std::for_each(cards->cards.begin(), cards->cards.end(), [&](std::pair<int, databasesModule::sCourseCard*> e) {
        currentCards.push_back(e);
    });
    std::random_device rd;
    auto rng = std::default_random_engine{ rd() };
    std::shuffle(std::begin(currentCards), std::end(currentCards), rng);
}

void examWindow::goToNextCard() {
//    todo start card from action
    if (currentCards.empty()) {
        // todo go to result window
    }
    auto cardHolder = findNode("cardHolder");
    auto bg = dynamic_cast<cocos2d::Sprite*>(findNode("bg"));
    // reset changes
    cardHolder->removeAllChildren();
    cardHolder->setOpacity(255);
    cardHolder->setRotation(0.f);
    bg->setColor(bgColor);

    auto card = new examCardWidget();
    cardHolder->addChild(card);
    auto cardData = currentCards.front();
    card->setData(cardData.second);
    card->setTouchClb([cardHolder, cardData, bg, this]() {
        auto fadeOut = FadeOut::create(.12);
        auto clb = cocos2d::CallFunc::create([cardHolder, cardData, bg, this]() {
            cardHolder->removeAllChildren();
            auto newCard = new resultCardWidget();
            cardHolder->addChild(newCard);
            newCard->setData(cardData.second, cardHolder, bg);
            newCard->setDefaultColor(bgColor);
            newCard->setSwipeClb([this](resultCardWidget::eCardSwipeDirection direction) {
                //todo register answer
                goToNextCard();
            });
        });
        auto fadeIn = FadeIn::create(.12);
        auto seq = Sequence::create(fadeOut, clb, fadeIn, nullptr);
        cardHolder->runAction(seq);
    });
}
