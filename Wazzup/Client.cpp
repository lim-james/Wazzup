#include "Client.h"

// modules
#include "TTS.h"
#include "Helpers.h"
#include "Browser.h"

ProcessMap Client::Create() {
	ProcessMap result;
	
	SafeAdd(TTS::Create(),		result, OP_TTS);
	SafeAdd(Browser::Create(),	result, OP_BROWSER);

	return result;
}

void Client::Destroy() {
	TTS::Destroy();
	Browser::Destroy();
}

PollCallback Client::GetPoll(std::string const & path) {
	const std::wstring domain = Helpers::ToUTF16("/dms/" + path + ".json", CP_UTF8);
	return ([domain]() -> std::string {
		const REST::Response response = REST::SendRequest(
			HOST,
			domain,
			L"GET",
			nullptr,
			0
		);

		return response.body.substr(1, response.body.length() - 2);
	});
}

void Client::Update(
	std::string const & message,
	ProcessMap const & map
)
{
	if (message[0] == '/') 
		ProcessCommand(message, map);
	else 
		map.at(OP_TTS)(message);
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

void Client::ProcessCommand(
	std::string const & message, 
	ProcessMap const & map
) {
	const size_t commandSize = message.find_first_of(' ');
	const std::string command = message.substr(1, commandSize - 1);
	const std::string body = message.substr(commandSize + 1);

	if (command == "open") 
		map.at(OP_BROWSER)(body);
}

