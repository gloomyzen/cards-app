#include "examCardWidget.h"
#include "common/coreModule/nodes/widgets/gridNode.h"
//#include <boost/locale.hpp>
//#include <boost/algorithm/string.hpp>
//#include <boost/iterator/filter_iterator.hpp>
#include "cocos-ext.h"
#include <clocale>
#include <locale>
#include <codecvt>

using namespace cardsApp::interfaceModule;

examCardWidget::examCardWidget() {
	this->setName("examCardWidget");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node *>(this));
	bgNode = dynamic_cast<cocos2d::ui::Scale9Sprite *>(findNode("cardBg"));
	setOnTouchBegan([this](cocos2d::Touch *touch, cocos2d::Event *event) {
		if (cardTouchClb)
			cardTouchClb();
	});
}

std::wstring utf8_to_wstring (const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.from_bytes(str);
}

std::string wstring_to_utf8 (const std::wstring& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes(str);
}

void examCardWidget::setData(int, cardsApp::databasesModule::sCourseCard *card) {
	auto capitalize = [](const std::string &line) {
		std::setlocale(LC_CTYPE, "en_US.UTF-8");
		auto wstr = utf8_to_wstring(line);
		for (auto it = wstr.begin(); it != wstr.end(); ++it) {
			if (it == wstr.begin()) {
				*it = std::toupper(*it);
			}
		}
		return wstring_to_utf8(wstr);
	};
	auto grid = dynamic_cast<common::coreModule::gridNode *>(findNode("gridContainer"));
	if (auto label = dynamic_cast<cocos2d::Label *>(findNode("firstWord"))) {
		label->setString(capitalize(card->ruWord));
	}
	if (!card->ruSentence.empty()) {
		auto label = new cocos2d::Label();
		label->setName("label");
		loadComponent("widgets/" + this->getName(), label);
		label->setString(capitalize(card->ruSentence));
		grid->addChild(label);
	}
	grid->updateGridTransform();
}
