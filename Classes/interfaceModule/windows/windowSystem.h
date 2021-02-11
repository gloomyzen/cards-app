#ifndef CARDS_APP_WINDOWSYSTEM_H
#define CARDS_APP_WINDOWSYSTEM_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace cardsApp::interfaceModule {

	class windowSystem : public common::coreModule::nodeProperties<cocos2d::Node> {
	public:
		enum class eWindowState {
			CLOSED = 0,
			OPENING,
			OPENED,
			CLOSING
		};
		windowSystem();
		~windowSystem() = default;

		CREATE_FUNC(windowSystem);

	private:
		eWindowState currentState = eWindowState::CLOSED;
	};
}//cardsApp::interfaceModule


#endif //CARDS_APP_WINDOWSYSTEM_H
