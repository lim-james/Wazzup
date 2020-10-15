#ifndef CLIENT_H
#define CLIENT_H

#include "Base.h"
#include "Rest.h"

#define REFRESH_DELAY 100

#define OP_TTS 0

namespace Client {

	ProcessMap Create();
	void Destroy();

	std::string Poll();

	void Update(
		std::string const & message,
		ProcessMap const & map
	);

	bool SafeAdd(
		Process const & process,
		ProcessMap & map,
		unsigned const & id
	);

};

#endif
