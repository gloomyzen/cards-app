#include "localProfileBlock.h"

using namespace cardsApp::localProfile;
using namespace rapidjson;


localProfileBlock::localProfileBlock() {}

localProfileBlock::~localProfileBlock() {}

bool localProfileBlock::load(const GenericValue<UTF8<char>>::ConstObject &data) {
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

bool sLocalProfileCourse::load(const GenericValue<UTF8<char>>::ConstObject &data) {
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
		auto array = _goodQuestion->value.GetArray();
		for (auto it = array.Begin(); it != array.End(); ++it) {
			if (it->IsInt()) {
				goodQuestion.push_back(it->GetInt());
			}
		}
	}
	if (_mediumQuestion != data.MemberEnd() && _mediumQuestion->value.IsArray()) {
		auto array = _mediumQuestion->value.GetArray();
		for (auto it = array.Begin(); it != array.End(); ++it) {
			if (it->IsInt()) {
				mediumQuestion.push_back(it->GetInt());
			}
		}
	}
	if (_badQuestion != data.MemberEnd() && _badQuestion->value.IsArray()) {
		auto array = _badQuestion->value.GetArray();
		for (auto it = array.Begin(); it != array.End(); ++it) {
			if (it->IsInt()) {
				badQuestion.push_back(it->GetInt());
			}
		}
	}
	return true;
}

bool localProfileBlock::save(Value &data, Document::AllocatorType &allocator) {
	data.SetArray();
	for (auto item : localCourses) {
		rapidjson::Value obj;
		obj.SetObject();
		if (item.second->save(obj, allocator)) {
			data.PushBack(obj, allocator);
		}
	}
	return true;
}

bool sLocalProfileCourse::save(Value &data, Document::AllocatorType &allocator) {
	data.AddMember("id", id, allocator);
	rapidjson::Value goodQuestionArray;
	goodQuestionArray.SetArray();
	for (auto item : goodQuestion) {
		goodQuestionArray.PushBack(item, allocator);
	}
	data.AddMember("goodQuestion", goodQuestionArray, allocator);
	rapidjson::Value mediumQuestionArray;
	mediumQuestionArray.SetArray();
	for (auto item : mediumQuestion) {
		mediumQuestionArray.PushBack(item, allocator);
	}
	data.AddMember("goodQuestion", mediumQuestionArray, allocator);
	rapidjson::Value badQuestionArray;
	badQuestionArray.SetArray();
	for (auto item : badQuestion) {
		badQuestionArray.PushBack(item, allocator);
	}
	data.AddMember("goodQuestion", badQuestionArray, allocator);
	return true;
}

sLocalProfileCourse *localProfileBlock::getCourse(int id) {
	if (localCourses.find(id) != localCourses.end()) {
		return localCourses.find(id)->second;
	}
	return nullptr;
}
