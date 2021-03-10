#include "notifyWindow.h"

using namespace cardsApp::interfaceModule;

notifyWindow::notifyWindow() {
    this->setName("notifyWindow");
    loadProperty("windows/" + this->getName(), dynamic_cast<Node*>(this));
}
