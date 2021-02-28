#ifndef CARDS_APP_STRINGFORMAT_H
#define CARDS_APP_STRINGFORMAT_H

#include <string>
#include <clocale>
#include <locale>
#include <codecvt>

namespace cardsApp::utilityModule {
	class stringFormat {
	public:
		enum class eLocaleType {
			EN = 0,
			RU,
		};
		static std::wstring utf8_to_wstring (const std::string& str) {
			std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
			return conv.from_bytes(str);
		}

		static std::string wstring_to_utf8 (const std::wstring& str) {
			std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
			return conv.to_bytes(str);
		}

		static std::string capitalizeString(const std::string &line, eLocaleType type = eLocaleType::EN) {
			switch (type) {
				case eLocaleType::EN: {
					std::setlocale(LC_CTYPE, "en_US.UTF-8");
					std::locale loc("en_US.UTF-8");
				}
					break;
				case eLocaleType::RU: {
					std::setlocale(LC_CTYPE, "ru_RU.UTF-8");
					std::locale loc("ru_RU.UTF-8");
				}
					break;
			}
			auto wstr = utf8_to_wstring(line);
			for (auto it = wstr.begin(); it != wstr.end(); ++it) {
				if (it == wstr.begin()) {
					*it = std::toupper(*it);
				} else {
					*it = std::tolower(*it);
				}
			}
			return wstring_to_utf8(wstr);
		};

		static std::string toLowerString(const std::string &line, eLocaleType type = eLocaleType::EN) {
			switch (type) {
				case eLocaleType::EN: {
					std::setlocale(LC_CTYPE, "en_US.UTF-8");
					std::locale loc("en_US.UTF-8");
				}
					break;
				case eLocaleType::RU: {
					std::setlocale(LC_CTYPE, "ru_RU.UTF-8");
					std::locale loc("ru_RU.UTF-8");
				}
					break;
			}
			auto wstr = utf8_to_wstring(line);
			for (auto it = wstr.begin(); it != wstr.end(); ++it) {
				*it = std::tolower(*it);
			}
			return wstring_to_utf8(wstr);
		};
	};
}

#endif //CARDS_APP_STRINGFORMAT_H
