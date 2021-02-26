#include "examCardWidget.h"
#include "common/coreModule/nodes/widgets/gridNode.h"
#include <boost/locale.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include "cocos-ext.h"

using namespace cardsApp::interfaceModule;

examCardWidget::examCardWidget() {
	this->setName("examCardWidget");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
	bgNode = dynamic_cast<cocos2d::ui::Scale9Sprite*>(findNode("cardBg"));
	setOnTouchBegan([this](cocos2d::Touch* touch, cocos2d::Event* event) {
		if (cardTouchClb)
			cardTouchClb();
	});
}

void examCardWidget::setData(int, cardsApp::databasesModule::sCourseCard* card) {
	auto capitalize = [](const std::string& line) {
		boost::locale::generator gen;
		std::locale loc = gen("");
		std::locale::global(loc);
		std::cout.imbue(loc);
		std::vector<std::string> splitVec;
		split( splitVec, line, boost::is_any_of(" "), boost::token_compress_on);
		if (splitVec.size() == 1) {
			std::string result;
			result = splitVec.front();
			boost::trim(result);
			result = boost::locale::to_upper(result);
			return result;
		} else {
			return line;
		}
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
