#include "Propeties.h"

#ifndef MASTER

#include "Client.h"

#include <windows.h>
#include <Lmcons.h>

#include <iostream>

int main() {

#ifndef _DEBUG
	FreeConsole();
#endif

	const ProcessMap map = Client::Create();
	std::string prev = "";

	char username[UNLEN + 1];
	DWORD usernameLength = UNLEN + 1;
	GetUserName(username, &usernameLength);
	
	PollCallback poll = Client::GetPoll(std::string(username, usernameLength));

	while (true) {
		const std::string current = poll();

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
