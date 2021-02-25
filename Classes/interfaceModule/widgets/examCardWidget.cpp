#include "examCardWidget.h"
#include "common/coreModule/nodes/widgets/gridNode.h"
#include <boost/locale.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iterator/filter_iterator.hpp>

using namespace cardsApp::interfaceModule;

examCardWidget::examCardWidget() {
	this->setName("examCardWidget");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
}

void examCardWidget::setData(int, cardsApp::databasesModule::sCourseCard* card) {
	auto capitalize = [](const std::string& line) {
		std::string result;
		boost::locale::generator gen;
		std::locale loc=gen("");
		std::locale::global(loc);
		std::cout.imbue(loc);
		std::vector<std::string> splitVec;
		split( splitVec, line, boost::is_any_of(" "), boost::token_compress_on);
		for (auto it = splitVec.begin(); it != splitVec.end(); ++it) {
			if (it == splitVec.begin()) {
				result += STRING_FORMAT(" %s", boost::locale::to_title(*it).c_str());
			} else {
				result += STRING_FORMAT(" %s", (*it).c_str());
			}
		}

		return result;
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
