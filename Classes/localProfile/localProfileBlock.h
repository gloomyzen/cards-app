#ifndef CARDS_APP_LOCALPROFILEBLOCK_H
#define CARDS_APP_LOCALPROFILEBLOCK_H

#include "common/profileModule/profileBlockInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace cardsApp {
	namespace localProfile {

	class localProfileBlock : public common::profileModule::profileBlockInterface {
	public:
		localProfileBlock();
		~localProfileBlock();

		bool load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject &) override;
		bool save(rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject &) override;
		};
	}
}


#endif //CARDS_APP_LOCALPROFILEBLOCK_H
