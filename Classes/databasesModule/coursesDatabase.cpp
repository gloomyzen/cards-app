#include "coursesDatabase.h"
#include "common/coreModule/resources/resourceManager.h"
#include "common/debugModule/logManager.h"

using namespace cardsApp::databasesModule;

coursesDatabase::coursesDatabase() {}

void coursesDatabase::load(const rapidjson::Document &data) {
	if (getPath().empty()) {
		LOG_ERROR("coursesDatabase::load: path is empty!");
		return;
	}
	if (!data.IsObject()) {
		LOG_ERROR(STRING_FORMAT("coursesDatabase::load: file from path %s is not object!", getPath().c_str()));
		return;
	}
	auto courses = data.FindMember("courses");
	if (courses != data.MemberEnd() && courses->value.IsArray()) {
		auto array = courses->value.GetArray();
		for (auto courseIt = array.Begin(); courseIt != array.End(); ++courseIt) {
			if (!courseIt->IsObject())
				continue;
			auto id = courseIt->FindMember("id");
			auto name = courseIt->FindMember("name");
			auto path = courseIt->FindMember("path");
			if (id == courseIt->MemberEnd() || name == courseIt->MemberEnd() || path == courseIt->MemberEnd()) {
				continue;
			}
			if (!id->value.IsInt() || !name->value.IsString() || !path->value.IsString()) {
				continue;
			}
			auto item = new sCourseBook();
			item->id = id->value.GetInt();
			item->name = name->value.GetString();
			auto json = GET_JSON_MANAGER()->loadJson(path->value.GetString());
			if (!json.HasParseError() && !json.IsNull() && item->load(json)) {
				coursesDb.insert({item->id, item});
			}

		}
	}

}

bool sCourseBook::load(const rapidjson::Document &data) {
	if (!data.IsArray()) {
		LOG_ERROR(STRING_FORMAT("sCourseBook::load: course '%d' - '%s' is not array!", id, name.c_str()));
		return false;
	}
	int ids = 0;
	for (auto it = data.Begin(); it != data.End(); ++it) {
		if (!it->IsObject()) {
			continue;
		}
		auto _enWord = it->FindMember("enWord");
		auto _enTranscription = it->FindMember("enTranscription");
		auto _enDescription = it->FindMember("enDescription");
		auto _enSentence = it->FindMember("enSentence");
		auto _ruWord = it->FindMember("ruWord");
		auto _ruSentence = it->FindMember("ruSentence");

		if (_enWord == it->MemberEnd() || !_enWord->value.IsString()
		|| _ruWord == it->MemberEnd() || !_ruWord->value.IsString()) {
			continue;
		}
		auto item = new sCourseCard();
		item->id = ids++;
		item->enWord = _enWord->value.GetString();
		item->ruWord = _ruWord->value.GetString();

		if (_enTranscription != it->MemberEnd() && _enTranscription->value.IsString())  {
			item->enTranscription = _enTranscription->value.GetString();
		}
		if (_enDescription != it->MemberEnd() && _enDescription->value.IsString())  {
			item->enDescription = _enDescription->value.GetString();
		}
		if (_enSentence != it->MemberEnd() && _enSentence->value.IsString())  {
			item->enSentence = _enSentence->value.GetString();
		}
		if (_ruSentence != it->MemberEnd() && _ruSentence->value.IsString())  {
			item->ruSentence = _ruSentence->value.GetString();
		}
		courses.insert({item->id, item});
	}

	return !courses.empty();
}
