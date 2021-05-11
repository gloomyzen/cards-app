#include "closeBtnWidget.h"
#include "cocos-ext.h"

using namespace cardsApp::interfaceModule;

closeBtnWidget::closeBtnWidget() {
    this->setName("closeBtnWidget");
    loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
}
std::deque<nodeTasks> closeBtnWidget::getTasks() {
    std::deque<nodeTasks> result;

    result.emplace_back([this]() {
        setButtonBgSprite(dynamic_cast<cocos2d::Sprite*>(findNode("btnBg")));
//        bgNode = dynamic_cast<cocos2d::ui::Scale9Sprite*>(findNode("btnBg"));
        setOnTouchEnded([this]() {
            if (closeClb) {
                closeClb();
            }
        });

        return eTasksStatus::STATUS_OK;
    });

    return result;
}
