#include "Client.h"

// modules
#include "TTS.h"

ProcessMap Client::Create() {
	ProcessMap result;
	
	SafeAdd(TTS::Create(), result, OP_TTS);

	return result;
}

void Client::Destroy() {
	TTS::Destroy();
}

std::string Client::Poll() {
	const REST::Response response = REST::SendRequest(
		L"wazzup-b5b3f.firebaseio.com",
		L"/broadcast.json",
		L"GET",
		nullptr,
		0
	);

	return response.body.substr(1, response.body.length() - 2);
}

void Client::Update(
	std::string const & message,
	ProcessMap const & map
)
{
	if (message[0] == '/') {
		// process commands
	} else {
		map.at(OP_TTS)(message);
	}
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

