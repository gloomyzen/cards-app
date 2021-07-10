#include "buttonIconWidget.h"
#include "cocos-ext.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/stringUtility.h"
#include <map>
#include <string>

using namespace cardsApp::interfaceModule;

const std::map<std::string, buttonIconWidget::eButtonBgColor> colorTypesMap = {
    { "white", buttonIconWidget::eButtonBgColor::WHITE },
    { "whiteBorder", buttonIconWidget::eButtonBgColor::WHITE_BORDER },
    { "red", buttonIconWidget::eButtonBgColor::RED }
};

const std::map<std::string, buttonIconWidget::eButtonIcon> iconTypesMap = {
    { "none", buttonIconWidget::eButtonIcon::NONE },
    { "return", buttonIconWidget::eButtonIcon::RETURN },
    { "recycle", buttonIconWidget::eButtonIcon::RECYCLE },
    { "close", buttonIconWidget::eButtonIcon::CLOSE }
};


buttonIconWidget::buttonIconWidget() {
    this->setName("buttonIconWidget");
    loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
}

std::deque<nodeTasks> buttonIconWidget::getTasks() {
    std::deque<nodeTasks> result;

    result.emplace_back([this]() {
        auto settings = getSettingsData();
        if (settings.IsObject() && settings.HasMember("color") && settings["color"].IsString()) {
            auto find = colorTypesMap.find(settings["color"].GetString());
            if (find != colorTypesMap.end()) {
                setBgColor(find->second);
            } else {
                LOG_ERROR(STRING_FORMAT("buttonIconWidget setting color exists and have incorrect value %s",
                                        settings["color"].GetString()));
            }
        } else {
            setBgColor(eButtonBgColor::WHITE);
        }
        if (settings.IsObject() && settings.HasMember("icon") && settings["icon"].IsString()) {
            auto find = iconTypesMap.find(settings["icon"].GetString());
            if (find != iconTypesMap.end()) {
                setIcon(find->second);
            } else {
                LOG_ERROR(STRING_FORMAT("buttonIconWidget setting icon exists and have incorrect value %s",
                                        settings["icon"].GetString()));
            }
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
        default:
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
    case eButtonBgColor::RED:
        loadComponent(button, "redButton");
        break;
    }
    setButtonBgSprite(dynamic_cast<cocos2d::Sprite*>(button));
}
