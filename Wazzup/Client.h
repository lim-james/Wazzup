#ifndef CLIENT_H
#define CLIENT_H

#include "Propeties.h"
#include "Base.h"
#include "Rest.h"

#include <functional>

typedef std::function<std::string()> PollCallback;

namespace Client {

	ProcessMap Create();
	void Destroy();

	std::string GetUsername();
	void SendPulse(std::string const & username);

	PollCallback GetPoll(std::string const & username);

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
