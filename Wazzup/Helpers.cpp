#include "Helpers.h"

std::wstring Helpers::ToUTF16(std::string const & str, int const & cp) {
	if (str.empty()) return std::wstring();
	int sz = MultiByteToWideChar(cp, 0, &str[0], (int)str.size(), 0, 0);
	std::wstring res(sz, 0);
	MultiByteToWideChar(cp, 0, &str[0], (int)str.size(), &res[0], sz);
	return res;
}

