#include "examCardWidget.h"
#include "common/coreModule/nodes/widgets/gridNode.h"
#include <unicode/unistr.h>
#include <unicode/ustream.h>
#include <unicode/locid.h>

using namespace cardsApp::interfaceModule;

examCardWidget::examCardWidget() {
	this->setName("examCardWidget");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
}

void examCardWidget::setData(int, cardsApp::databasesModule::sCourseCard* card) {
	auto capitalize = [](std::string str){
		if (str.empty()) {
			return str;
		}
		str = "test";
//		std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){
//			return std::tolower(c);
//		});
		icu::UnicodeString ustring(str.c_str());
		icu::UnicodeString temp = ustring;
//		icu::BreakIterator* bi = icu_67::BreakIterator::cre
		temp.toUpper();
		temp.toUTF8String(str);
		return str;
	};
	auto grid = dynamic_cast<common::coreModule::gridNode*>(findNode("gridContainer"));
	if (auto label = dynamic_cast<cocos2d::Label*>(findNode("firstWord"))) {
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
