#include "Browser.h"

#include "Helpers.h"

#include <Windows.h>

Process Browser::Create() {
	return Open;
}

void Browser::Destroy() {}

std::string Browser::Open(std::string content) {
	ShellExecute(0, 0, content.c_str(), 0, 0, SW_SHOW);
	return "";
}
