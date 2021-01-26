#include "Propeties.h"

#ifndef MASTER

#include "Client.h"


#include <iostream>

int main() {

#ifndef _DEBUG
	FreeConsole();
#endif

	const ProcessMap map = Client::Create();
	std::string prev = "";

	// send pulse to server
	const std::string username = Client::GetUsername();
	Client::SendPulse(username);
	
	PollCallback poll = Client::GetPoll(username);

	while (true) {
		const std::string current = poll();

		if (current != prev) {
			Client::Update(current, map);
			prev = current;
		}
		
		Sleep(REFRESH_DELAY);
	}

	Client::Destroy();

	return 0;
}

#endif
