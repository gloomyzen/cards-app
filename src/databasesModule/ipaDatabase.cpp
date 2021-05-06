#include "ipaDatabase.h"
#include "common/coreModule/resources/resourceManager.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/stringUtility.h"

using namespace cardsApp::databasesModule;

static std::string emptyString{};

ipaDatabase::ipaDatabase() {}

void ipaDatabase::load(const rapidjson::Document& data) {
    if (getPath().empty()) {
        LOG_ERROR("ipaDatabase::load: path is empty!");
        return;
    }
    if (!data.IsObject()) {
        LOG_ERROR(STRING_FORMAT("ipaDatabase::load: file from path %s is not object!", getPath().c_str()));
        return;
    }
    auto letters = data.FindMember("letters");
    if (letters != data.MemberEnd() && letters->value.IsArray()) {
        auto array = letters->value.GetArray();
        for (auto lettersIt = array.Begin(); lettersIt != array.End(); ++lettersIt) {
            if (!lettersIt->IsObject())
                continue;
            auto letter = lettersIt->FindMember("letter");
            auto path = lettersIt->FindMember("path");
            if (letter == lettersIt->MemberEnd() || path == lettersIt->MemberEnd() || !letter->value.IsString()
                || !path->value.IsString()) {
                continue;
            }
            auto json = GET_JSON_MANAGER()->loadJson(path->value.GetString());
            if (!loadDictionary(letter->value.GetString(), json)) {
                LOG_ERROR(
                    STRING_FORMAT("ipaDatabase::load: file from path %s has incorrect formatting!", getPath().c_str()));
            }
        }
    }
}

bool ipaDatabase::loadDictionary(const std::string& mapKey, const rapidjson::Document& data) {
    if (data.HasParseError() || data.IsNull() || !data.IsArray()) {
        return false;
    }
    sLetter tempLetter;
    for (auto it = data.Begin(); it != data.End(); ++it) {
        if (!it->IsObject()) {
            continue;
        }
        auto _key = it->FindMember("key");
        auto _val = it->FindMember("val");
        if (_key == it->MemberEnd() || _val == it->MemberEnd() || !_key->value.IsString() || !_val->value.IsString())
            continue;
        tempLetter.insert({ _key->value.GetString(), _val->value.GetString() });
    }
    stringMapDb.insert({ mapKey, tempLetter });
    return true;
}

const std::string& ipaDatabase::findString(const std::string& word) const {
    auto string = common::utilityModule::stringUtility::trim(word);
    string = common::utilityModule::stringUtility::toLowerString(string);
    if (string.empty())
        return emptyString;
    std::string letter = string.substr(0, 1);
    if (letter.empty())
        return emptyString;
    if (stringMapDb.find(letter) != stringMapDb.end()) {
        auto dictionary = stringMapDb.find(letter)->second;
        if (dictionary.find(word) != dictionary.end()) {
            return dictionary.find(word)->second;
        }
    }

    return emptyString;
}
