#ifndef CARDS_APP_CARDPROGRESSBAR_H
#define CARDS_APP_CARDPROGRESSBAR_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace cardsApp::interfaceModule {

	class cardProgressBar : public common::coreModule::nodeProperties<cocos2d::Sprite> {
	public:
		cardProgressBar();
		~cardProgressBar() = default;

		CREATE_FUNC(cardProgressBar);

		void setProgress(int i = 0);

	protected:
		cocos2d::Sprite* progressBar = nullptr;
	};
}


#endif //CARDS_APP_CARDPROGRESSBAR_H
