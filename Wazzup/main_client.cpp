#include "Propeties.h"

#ifndef MASTER

#include "Client.h"
#include "Rest.h"

#include <iostream>

int main() {

#ifndef _DEBUG
	FreeConsole();
#endif

	const ProcessMap map = Client::Create();

	// send pulse to server
	const std::string username = Client::GetUsername();
	Client::SendPulse(username, Client::ResponseHandler);
	
	// fetch initial 
	PollCallback poll = Client::GetPoll(username);
	std::string prev = poll();

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
