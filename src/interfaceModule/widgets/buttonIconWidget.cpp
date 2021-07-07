#include "buttonIconWidget.h"
#include "cocos-ext.h"

using namespace cardsApp::interfaceModule;

buttonIconWidget::buttonIconWidget() {
    this->setName("buttonIconWidget");
    loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
}

std::deque<nodeTasks> buttonIconWidget::getTasks() {
    std::deque<nodeTasks> result;

    result.emplace_back([this]() {
        auto bg = new cocos2d::ui::Scale9Sprite();
        bg->setName("btnBg");
        loadComponent(bg);
        setButtonBgSprite(dynamic_cast<cocos2d::Sprite*>(bg));
        setOnTouchEnded([this]() {
            if (closeClb) {
                closeClb();
            }
        });

        return eTasksStatus::STATUS_OK;
    });

    return result;
}

void buttonIconWidget::buttonClickClb(const std::function<void()>& clb) {
    closeClb = clb;
}

void buttonIconWidget::setIcon(buttonIconWidget::eButtonIcon type) {
    switch (type) {
    case buttonIconWidget::eButtonIcon::CLOSE:
        if (auto node = findNode("icon")) {
            loadComponent(node, "closeIcon");
        }
        break;
    case eButtonIcon::RECYCLE:
        if (auto node = findNode("icon")) {
            loadComponent(node, "recycleIcon");
        }
        break;
    }
}