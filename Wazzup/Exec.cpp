#include "Exec.h"

#include <cstdio>

Process Exec::Create() {
	return Run;
}

void Exec::Destroy() {}

std::string Exec::Run(std::string cmd) {
	FILE* pipe = _popen(cmd.c_str(), "r");
	if (!pipe) return "\"popen() failed!\"";

	std::string result = "[";
	char buffer[128];
	while (fgets(buffer, 128, pipe)) 
		result += '"' + std::string(buffer, strlen(buffer) - 1) + "\",";

	_pclose(pipe);

	result.pop_back();

	return result + ']';
}
