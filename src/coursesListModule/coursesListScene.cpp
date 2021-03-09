#include "coursesListScene.h"
#include "common/coreModule/gameManager.h"
#include "common/coreModule/nodes/widgets/gridNode.h"
#include "common/coreModule/scenes/windows/windowBase.h"
#include "databasesModule/coursesTool.h"
#include "interfaceModule/widgets/cardWidget.h"

using namespace cardsApp::coursesListModule;
using namespace cardsApp::interfaceModule;
using namespace cocos2d;

coursesListScene::coursesListScene() {
    this->setName("coursesListScene");
    loadProperty(STRING_FORMAT("coursesListScene/%s", this->getName().c_str()), this);
}

coursesListScene::~coursesListScene() {}

std::deque<nodeTasks> coursesListScene::getTasks() {
    std::deque<nodeTasks> result;
    result.emplace_back([this]() {
        scrollView = dynamic_cast<ui::ScrollView*>(findNode("scrollContainer"));

        return eTasksStatus::STATUS_OK;
    });

    result.emplace_back([this]() {
        databasesModule::coursesTool tool;
        auto grid = dynamic_cast<common::coreModule::gridNode*>(findNode("gridContainer"));
        if (grid == nullptr) {
            LOG_ERROR("coursesListScene::getTasks: grid not found!");
            return eTasksStatus::STATUS_ERROR_BREAK;
        }
        auto list = tool.getCoursesWithProgress();
        for (auto item : list) {
            auto card = new cardWidget();
            auto cardsId = item.first;
            auto courseName = item.second.second->name;
            card->setOnTouchEnded([cardsId, courseName, card](cocos2d::Touch* touch, cocos2d::Event* event) {
                if (auto window = GET_GAME_MANAGER().requestWindow("coursePreviewWindow")) {
                    window->setData("cardsId", cardsId);
                    window->setData("courseName", courseName);
                    window->setData("onClose", [card, cardsId]() {
                        databasesModule::coursesTool tool;
                        auto list = tool.getCoursesWithProgress();
                        auto find = list.find(cardsId);
                        if (find != list.end()) {
                            card->initCard(find->second);
                        }
                    });
                }
            });
            card->initCard(item.second);
            card->setSwallowTouches(false);
            grid->addChild(card);
        }
        grid->updateGridTransform();
        scrollView->setInnerContainerSize(grid->getContentSize());

        return eTasksStatus::STATUS_OK;
    });

    return result;
}
