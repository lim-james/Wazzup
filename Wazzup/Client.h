#ifndef CLIENT_H
#define CLIENT_H

#include "Base.h"
#include "Rest.h"

#define REFRESH_DELAY 100

#define OP_TTS		0
#define OP_BROWSER	1

namespace Client {

	ProcessMap Create();
	void Destroy();

	std::string Poll();

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
