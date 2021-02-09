#include "cardProgressBar.h"

using namespace cardsApp::interfaceModule;

cardProgressBar::cardProgressBar() {
	this->setName("cardProgressBar");
	loadProperty("widgets/" + this->getName(), dynamic_cast<cocos2d::Sprite*>(this));
	progressBar = dynamic_cast<cocos2d::Sprite*>(findNode("progressBar"));
	setProgress(0);
}

void cardProgressBar::setProgress(int i) {
	if (i < 0) i = 0;
	else if (i > 100) i = 100;
	progressBar->setScaleX( 1.f / 100 * i);
}
