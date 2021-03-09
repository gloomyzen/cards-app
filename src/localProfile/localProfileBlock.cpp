#include "localProfileBlock.h"

using namespace cardsApp::localProfile;
using namespace rapidjson;


localProfileBlock::localProfileBlock() {}

localProfileBlock::~localProfileBlock() {
    for (auto item : localCourses) {
        delete item.second;
    }
    localCourses.clear();
}

bool localProfileBlock::load(const GenericValue<UTF8<char>>::ConstObject& data) {
    auto coursesArray = data.FindMember("courses");
    if (!coursesArray->value.IsArray()) {
        return true;
    }
    auto courses = coursesArray->value.GetArray();
    for (auto it = courses.Begin(); it != courses.End(); ++it) {
        if (it->IsObject()) {
            auto item = new sLocalProfileCourse();
            if (item->load(it->GetObjectJ())) {
                localCourses.insert({ item->id, item });
            }
        }
    }
    return true;
}

bool sLocalProfileCourse::load(const GenericValue<UTF8<char>>::ConstObject& data) {
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

bool localProfileBlock::save(Value& data, Document::AllocatorType& allocator) {
    Value array;
    array.SetArray();
    for (auto item : localCourses) {
        rapidjson::Value obj;
        obj.SetObject();
        if (item.second->save(obj, allocator)) {
            array.PushBack(obj, allocator);
        }
    }
    rapidjson::Value key("courses", allocator);
    data.AddMember(key, array, allocator);
    return true;
}

bool sLocalProfileCourse::save(Value& data, Document::AllocatorType& allocator) {
    data.AddMember("id", id, allocator);
    rapidjson::Value goodQuestionArray;
    goodQuestionArray.SetArray();
    for (auto item : goodQuestion) { goodQuestionArray.PushBack(item, allocator); }
    data.AddMember("goodQuestion", goodQuestionArray, allocator);
    rapidjson::Value mediumQuestionArray;
    mediumQuestionArray.SetArray();
    for (auto item : mediumQuestion) { mediumQuestionArray.PushBack(item, allocator); }
    data.AddMember("goodQuestion", mediumQuestionArray, allocator);
    rapidjson::Value badQuestionArray;
    badQuestionArray.SetArray();
    for (auto item : badQuestion) { badQuestionArray.PushBack(item, allocator); }
    data.AddMember("goodQuestion", badQuestionArray, allocator);
    return true;
}

void sLocalProfileCourse::updateAnswers(int cardId, bool isCorrect) {
    auto findAnswer = [](std::vector<int>& list, int id, bool correct) {
           auto it = std::find_if(list.begin(), list.end(), [id](int i) { return i == id; });
           bool result = it != list.end();
           if (result) {
               list.erase(it);
           }
           return result;
    };
    bool isBad = findAnswer(badQuestion, cardId, isCorrect);
    bool isMed = findAnswer(mediumQuestion, cardId, isCorrect);
    bool isGood = findAnswer(goodQuestion, cardId, isCorrect);
    if (!isBad && !isMed && !isGood) {
        if (isCorrect) {
            mediumQuestion.push_back(cardId);
        } else {
            badQuestion.push_back(cardId);
        }
    } else {
        if (isBad) {
            if (isCorrect) {
                mediumQuestion.push_back(cardId);
            } else {
                badQuestion.push_back(cardId);
            }
        } else if (isMed) {
            if (isCorrect) {
                goodQuestion.push_back(cardId);
            } else {
                mediumQuestion.push_back(cardId);
            }
        } else {
            if (isCorrect) {
                goodQuestion.push_back(cardId);
            } else {
                mediumQuestion.push_back(cardId);
            }
        }
    }
}

sLocalProfileCourse* localProfileBlock::getCourse(int id) {
    if (localCourses.find(id) != localCourses.end()) {
        return localCourses.find(id)->second;
    } else {
        localCourses[id] = new sLocalProfileCourse();
        localCourses[id]->id = id;
    }
    return localCourses[id];
}
