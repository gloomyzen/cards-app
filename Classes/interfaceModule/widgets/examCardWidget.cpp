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
		std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){
			return std::tolower(c);
		});
//		str[0] = static_cast<std::string::value_type>(toupper(str[0]));
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
