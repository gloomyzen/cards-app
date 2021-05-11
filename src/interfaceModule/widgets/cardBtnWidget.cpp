#include "cardBtnWidget.h"
#include "cocos-ext.h"

using namespace cardsApp::interfaceModule;

cardBtnWidget::cardBtnWidget() {
    this->setName("cardBtnWidget");
    loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
    auto bg = new cocos2d::ui::Scale9Sprite();
    bg->setName("cardBg");
    loadComponent(bg);
    setButtonBgSprite(dynamic_cast<cocos2d::Sprite*>(bg));
    label = dynamic_cast<cocos2d::Label*>(findNode("btnText"));
}

void cardBtnWidget::setText(const std::string& value) { label->setString(value); }
