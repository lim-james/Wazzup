#ifndef HELPERS_H
#define HELPERS_H

#include <Windows.h>
#include <string>

namespace Helpers {
	std::wstring ToUTF16(std::string const& str, int const& cp);
}

#endif
