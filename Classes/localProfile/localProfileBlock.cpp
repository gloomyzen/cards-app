#include "localProfileBlock.h"

using namespace cardsApp::localProfile;


localProfileBlock::localProfileBlock() {}

localProfileBlock::~localProfileBlock() {}

bool localProfileBlock::load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject& data) {
	auto coursesArray = data.FindMember("courses");
	if (!coursesArray->value.IsArray()) {
		return true;
	}
	auto courses = coursesArray->value.GetArray();
	for (auto it = courses.Begin(); it != courses.End(); ++it) {
		if (it->IsObject()) {
			auto item = new sLocalProfileCourse();
			if (item->load(it->GetObjectJ())) {
				localCourses.insert({item->id, item});
			}
		}

	}
	return true;
}

bool localProfileBlock::save(rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject& data) {
	return false;
}

bool sLocalProfileCourse::load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject& data) {
	auto _id = data.FindMember("id");
	auto _goodQuestion = data.FindMember("goodQuestion");
	auto _mediumQuestion = data.FindMember("mediumQuestion");
	auto _badQuestion = data.FindMember("badQuestion");
	if (_id != data.MemberEnd() && _id->value.IsInt()) {
		id = _id->value.GetInt();
	} else {
		return false;
	}
	if (_goodQuestion != data.MemberEnd() && _goodQuestion->value.IsArray()) {
//		id = _id->value.GetInt();
	}
	return false;
}
