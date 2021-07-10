#include "buttonIconWidget.h"
#include "cocos-ext.h"
#include "cocos-ext.h"

using namespace cardsApp::interfaceModule;

buttonIconWidget::buttonIconWidget() {
    this->setName("buttonIconWidget");
    loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
}

std::deque<nodeTasks> buttonIconWidget::getTasks() {
    std::deque<nodeTasks> result;

    result.emplace_back([this]() {
        auto settings = getSettingsData();
        if (settings.IsObject()) {
            if (settings.HasMember("color") && settings["color"].IsString()) {
                //
            }
        } else {
            setBgColor(eButtonBgColor::WHITE);
        }

        return eTasksStatus::STATUS_OK;
    });

    result.emplace_back([this]() {
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
    if (auto node = findNode("icon")) {
        switch (type) {
        case buttonIconWidget::eButtonIcon::CLOSE:
            loadComponent(node, "closeIcon");
            break;
        case eButtonIcon::RECYCLE:
            loadComponent(node, "recycleIcon");
            break;
        case eButtonIcon::RETURN:
            loadComponent(node, "returnIcon");
            break;
        }
    }
}

void buttonIconWidget::setBgColor(buttonIconWidget::eButtonBgColor color) {
    auto button = new cocos2d::ui::Scale9Sprite();
    button->setName("btn");
    switch (color) {
    case eButtonBgColor::WHITE:
        loadComponent(button, "whiteButton");
        break;
    case eButtonBgColor::WHITE_BORDER:
        loadComponent(button, "whiteBorderButton");
        break;
    }
    setButtonBgSprite(dynamic_cast<cocos2d::Sprite*>(button));
}
