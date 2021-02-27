#ifndef CARDS_APP_STRINGFORMAT_H
#define CARDS_APP_STRINGFORMAT_H

#include <string>
#include <clocale>
#include <locale>
#include <codecvt>

namespace cardsApp::utilityModule {
	class stringFormat {
	public:
		static std::wstring utf8_to_wstring (const std::string& str) {
			std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
			return conv.from_bytes(str);
		}

		static std::string wstring_to_utf8 (const std::wstring& str) {
			std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
			return conv.to_bytes(str);
		}

		static std::string capitalizeString(const std::string &line) {
//			std::setlocale(LC_CTYPE, "en_US.UTF-8");
			std::setlocale(LC_CTYPE, "ru_RU.UTF-8");
			auto wstr = utf8_to_wstring(line);
			for (auto it = wstr.begin(); it != wstr.end(); ++it) {
				if (it == wstr.begin()) {
					*it = std::toupper(*it);
				}
			}
			return wstring_to_utf8(wstr);
		};
	};
}

#endif //CARDS_APP_STRINGFORMAT_H
