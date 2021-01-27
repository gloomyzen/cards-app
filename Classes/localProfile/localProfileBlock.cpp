#include "localProfileBlock.h"

using namespace cardsApp::localProfile;


localProfileBlock::localProfileBlock() {}

localProfileBlock::~localProfileBlock() {}

bool localProfileBlock::load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject& data) {
	auto test = data.FindMember("courses");
	auto test2 = test->name.GetString();
	auto test3 = test->value.IsArray();
	auto test4 = "";
	return false;
}

bool localProfileBlock::save(rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject& data) {
	return false;
}

bool sLocalProfileCourse::load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject& data) {
	return false;
}
