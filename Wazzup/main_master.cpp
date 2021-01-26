#include "Propeties.h"

#ifdef MASTER

#include "Helpers.h"
#include "Rest.h"

#include <iostream>
#include <string>

int main() {

	std::cout << "Welcome back.\n";

	while (true) {
		std::string target = "";
		std::string buffer = "";

		std::cout << "> ";
		std::cin >> target;
		std::getline(std::cin, buffer);

		const std::wstring path = Helpers::ToUTF16("/dms/" + target + ".json", CP_UTF8);

		buffer = '"' + buffer + '"';
		REST::Response response = REST::SendRequest(
			HOST,
			path,
			L"PUT",
			(void*)buffer.c_str(),
			buffer.size()
		);

		std::cout << response.body << '\n';
	}

	return 0;
}

#endif

