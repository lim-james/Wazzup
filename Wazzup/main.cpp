//#define MASTER

#ifdef MASTER

#include "Rest.h"

#include <iostream>
#include <string>

int main() {

	std::cout << "Welcome back.\n";

	while (true) {
		std::string buffer = "";

		std::cout << "> ";
		std::getline(std::cin, buffer);

		buffer = '"' + buffer + '"';
		REST::Response response = REST::SendRequest(
			L"wazzup-b5b3f.firebaseio.com",
			L"/broadcast.json",
			L"PUT",
			(void*)buffer.c_str(),
			buffer.size()
		);

		std::cout << response.body << '\n';
	}

	return 0;
}

#else

#include "Client.h"

int main() {

	FreeConsole();

	const ProcessMap map = Client::Create();

	std::string prev = "";

	while (true) {
		const std::string current = Client::Poll();

		if (current != prev) {
			Client::Update(current, map);
			prev = current;
		}
		
		Sleep(REFRESH_DELAY);
	}

	//pVoice->Release();
	//pVoice = NULL;

	Client::Destroy();

	return 0;
}

#endif
