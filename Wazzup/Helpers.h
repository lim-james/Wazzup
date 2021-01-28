#ifndef HELPERS_H
#define HELPERS_H

#include <Windows.h>
#include <string>
#include <vector>

namespace Helpers {
	std::wstring ToUTF16(std::string const & str, int const & cp);
	std::string Trim(std::string s);
}

#endif
