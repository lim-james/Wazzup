#ifndef CLIENT_H
#define CLIENT_H

#include "Base.h"
#include "Rest.h"

#include <functional>

#define HOST L"wazzup-b5b3f.firebaseio.com"
#define REFRESH_DELAY 100

#define OP_TTS		0
#define OP_BROWSER	1

typedef std::function<std::string()> PollCallback;

namespace Client {

	ProcessMap Create();
	void Destroy();

	PollCallback GetPoll(std::string const & path);

	void Update(
		std::string const & message,
		ProcessMap const & map
	);

	// helper methods

	bool SafeAdd(
		Process const & process,
		ProcessMap & map,
		unsigned const & id
	);

	void ProcessCommand(
		std::string const & message,
		ProcessMap const & map
	);

};

#endif
