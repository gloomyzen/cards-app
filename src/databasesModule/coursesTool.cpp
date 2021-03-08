#include "coursesTool.h"
#include "common/debugModule/logManager.h"

using namespace cardsApp::databasesModule;
using namespace cardsApp::localProfile;


coursesTool::coursesTool() {
    courseDb = GET_DATABASE_MANAGER().getDatabase<coursesDatabase>("coursesDb");
    ipaDb = GET_DATABASE_MANAGER().getDatabase<ipaDatabase>("ipaDb");
    localProfile = GET_PROFILE().getBlock<localProfileBlock>("local");
}

coursesTool::~coursesTool() {}

std::map<int, std::pair<int, sCourseBook*>> coursesTool::getCoursesWithProgress() {
    std::map<int, std::pair<int, sCourseBook*>> result;
    if (courseDb == nullptr || localProfile == nullptr) {
        LOG_ERROR("coursesTool::getCoursesWithProgress: databases is not loaded!");
        return result;
    }

    auto list = courseDb->getCourses();
    for (const auto& [id, book] : list) {
        auto currentCourse = localProfile->getCourse(book->id);
        if (currentCourse == nullptr) {
            result.insert({ id, { 0, book } });
        } else {
            auto progress =
                100 / static_cast<float>(book->cards.size())
                * static_cast<float>(currentCourse->goodQuestion.size() + currentCourse->mediumQuestion.size());
            result.insert({ id, { progress, book } });
        }
    }
    return result;
}
