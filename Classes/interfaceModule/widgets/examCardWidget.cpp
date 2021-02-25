#include "examCardWidget.h"
#include "common/coreModule/nodes/widgets/gridNode.h"
#include <boost/locale.hpp>

using namespace cardsApp::interfaceModule;

examCardWidget::examCardWidget() {
	this->setName("examCardWidget");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
}

void examCardWidget::setData(int, cardsApp::databasesModule::sCourseCard* card) {
	auto capitalize = [](std::string line)  {
		boost::locale::generator gen;
		std::locale loc=gen("");
		std::locale::global(loc);
		std::cout.imbue(loc);
		line = boost::locale::to_title(line);
		return line;
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
