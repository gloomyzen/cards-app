#include "coursePreviewWindow.h"
#include "common/coreModule/nodes/widgets/gridNode.h"
#include "common/utilityModule/stringUtility.h"

#include "common/databaseModule/databaseInterface.h"
#include "databasesModule/coursesDatabase.h"
#include "databasesModule/coursesTool.h"
#include "databasesModule/databaseManager.h"
#include "interfaceModule/widgets/buttonIconWidget.h"
#include "interfaceModule/widgets/cardBtnWidget.h"

using namespace cardsApp::interfaceModule;
using namespace cardsApp::databasesModule;
using namespace common::coreModule;

coursePreviewWindow::coursePreviewWindow() {
    this->setName("coursePreviewWindow");
    loadProperty("windows/" + this->getName(), dynamic_cast<Node*>(this));
    setHandleMissClick(false);
}

coursePreviewWindow::~coursePreviewWindow() = default;

std::deque<nodeTasks> coursePreviewWindow::getTasks() {
    std::deque<nodeTasks> result;

    result.emplace_back([this]() {
        if (auto closeBtn = dynamic_cast<soundButton*>(findNode("closeBtn"))) {
            closeBtn->setOnTouchEnded([this]() {
                auto closeClb = getCallback("onClose");
                if (closeClb)
                    closeClb();
                closeWindow();
            });
        }

        return eTasksStatus::STATUS_OK;
    });

    result.emplace_back([this]() {
        auto cardsId = getData("cardsId", 0);
        auto courseName = getData("courseName", std::string());
        if (cardsId && !courseName.empty()) {
            showList(cardsId, courseName);
            if (auto label = dynamic_cast<Label*>(findNode("windowTitle"))) {
                label->setString(courseName);
            }
        }

        return eTasksStatus::STATUS_OK;
    });

    result.emplace_back([this]() {
        if (auto closeBtn = dynamic_cast<buttonIconWidget*>(findNode("buttonIconWidget"))) {
            closeBtn->setIcon(buttonIconWidget::eButtonIcon::RECYCLE);
            closeBtn->buttonClickClb([this]() {
                if (auto window = GET_GAME_MANAGER().requestWindow("notifyWindow", true)) {
                    auto cardsId = getData<int>("cardsId", 0);
                    auto closeClb = getCallback("onClose");
                    window->setCallback("onClose", [cardsId, closeClb]() {
                        databasesModule::coursesTool tool;
                        tool.resetProgress(cardsId);
                        if (closeClb)
                            closeClb();
                    });
                }
            });
        }

        return eTasksStatus::STATUS_OK;
    });

    return result;
}

void coursePreviewWindow::showList(int cardsId, const std::string& name) {
    auto scrollView = dynamic_cast<ui::ScrollView*>(findNode("scrollContainer"));
    if (!scrollView) {
        return;
    }
    auto coursesDb = GET_DATABASE_MANAGER().getDatabase<coursesDatabase>(databaseManager::eDatabaseList::COURSES_DB);
    auto cards = coursesDb->getCourseById(cardsId);
    auto grid = new gridNode();
    grid->setName("grid");
    loadComponent(grid);
    scrollView->addChild(grid);
    int cntWords = 0;
    for (auto item : cards->cards) {
        auto label = new Label();
        label->setName("label");
        loadComponent(label);
        grid->addChild(label);
        label->setString(STRING_FORMAT("%d. %s", ++cntWords, item.second->enWord.c_str()));
    }
    grid->updateGridTransform();
    scrollView->setInnerContainerSize(grid->getContentSize());
    if (scrollView->getContentSize().height < grid->getContentSize().height) {
        scrollView->setScrollBarEnabled(true);
        scrollView->setScrollBarColor(cocos2d::Color3B(255, 255, 255));
        scrollView->setScrollBarAutoHideEnabled(false);
    }
    if (auto btn = dynamic_cast<cardBtnWidget*>(findNode("cardBtnWidget"))) {
        btn->setOnTouchEnded([cardsId, name]() {
            if (auto window = GET_GAME_MANAGER().requestWindow("examWindow", true)) {
                window->setData("cardsId", cardsId);
                window->setData("courseName", name);
            }
        });
    }
}