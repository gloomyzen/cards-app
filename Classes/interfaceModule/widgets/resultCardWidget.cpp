#include "resultCardWidget.h"
#include "common/utilityModule/stringUtility.h"
#include "common/coreModule/nodes/widgets/gridNode.h"
#include "common/debugModule/logManager.h"

using namespace cardsApp::interfaceModule;
using namespace cocos2d::network;
using namespace common::utilityModule;

resultCardWidget::resultCardWidget() {
	this->setName("resultCardWidget");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node *>(this));
}

void resultCardWidget::setData(cardsApp::databasesModule::sCourseCard* card) {
	sendRequest(card->enWord);
	auto grid = dynamic_cast<common::coreModule::gridNode *>(findNode("gridContainer"));
	if (auto label = dynamic_cast<cocos2d::Label *>(findNode("firstWord"))) {
		label->setString(stringUtility::capitalizeString(card->enWord, stringUtility::eLocaleType::EN));
	}
	if (!card->enDescription.empty()) {
		auto label = new cocos2d::Label();
		label->setName("labelDescription");
		loadComponent("widgets/" + this->getName(), label);
		label->setString(STRING_FORMAT("(%s)", stringUtility::capitalizeString(card->enDescription, stringUtility::eLocaleType::EN).c_str()));
		grid->addChild(label);
	}
	if (!card->enSentence.empty()) {
		auto label = new cocos2d::Label();
		label->setName("label");
		loadComponent("widgets/" + this->getName(), label);
		label->setString(stringUtility::capitalizeString(card->enSentence, stringUtility::eLocaleType::EN));
		grid->addChild(label);
	}
	grid->updateGridTransform();
}

void resultCardWidget::sendRequest(const std::string &name) {
	auto* request = new (std::nothrow) HttpRequest();
	request->setUrl(STRING_FORMAT("https://source.unsplash.com/400x400/?%s", stringUtility::toLowerString(name, stringUtility::eLocaleType::EN).c_str()));
	request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(resultCardWidget::insertImage, this));
	request->setTag("Get image");
	HttpClient::getInstance()->send(request);
	request->release();
}

void resultCardWidget::insertImage(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response) {
	auto grid = dynamic_cast<common::coreModule::gridNode *>(findNode("gridContainer"));
	LOG_INFO("AppDelegate::onHttpRequestCompleted - onHttpRequestCompleted BEGIN");
	if (!response) {
		LOG_ERROR("onHttpRequestCompleted - No Response");
		return;
	}
	LOG_INFO(STRING_FORMAT("onHttpRequestCompleted - Response code: %lu", response->getResponseCode()));

	if (!response->isSucceed()) {
		LOG_ERROR("onHttpRequestCompleted - Response failed");
		LOG_ERROR(STRING_FORMAT("onHttpRequestCompleted - Error buffer: %s", response->getErrorBuffer()));
		return;
	}
	LOG_INFO(STRING_FORMAT("onHttpRequestCompleted - Response code: %s", response->getResponseDataString()));

	std::vector<char> *buffer = response->getResponseData();
	const char* file_char = buffer->data();
	LOG_INFO(STRING_FORMAT("onHttpRequestCompleted - Response code: %s", file_char));
	auto* image = new cocos2d::Image ();
	image->initWithImageData ( reinterpret_cast<const unsigned char*>(&(buffer->front())), buffer->size());
	auto* texture = new cocos2d::Texture2D ();
	texture->initWithImage (image);
	auto sprite = cocos2d::Sprite::createWithTexture(texture);
	sprite->setTexture(texture);
	grid->addChild(sprite, 0);
	sprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	sprite->setPivotPoint(cocos2d::Vec2(0.5f, 0.5f));

	LOG_INFO(STRING_FORMAT("onHttpRequestCompleted height %f", sprite->getContentSize().height));
	grid->updateGridTransform();
}
