#ifndef CLIENT_H
#define CLIENT_H

#include "Propeties.h"
#include "Base.h"
#include "Rest.h"

#include <functional>

typedef std::function<std::string()> PollCallback;
typedef std::function<void()> PulseCallback;
typedef std::function<std::string()> MonitorCallback;

namespace Client {

	/// Initialise client map
	ProcessMap Create();
	/// Destructor
	void Destroy();

	/// Returns device username
	std::string GetUsername();

	/// Returns a monitor of the state
	MonitorCallback GetMonitor(std::string const & username);
	/// Returns a pulse function with username
	PulseCallback GetPulse(
		std::string const & username, 
		REST::ResponseCallback callback
	);
	/// Returns the poll function with username
	PollCallback GetPoll(std::string const & username);

	bool SafeAdd(
		Process const & process,
		ProcessMap & map,
		unsigned const & id
	);

	std::string ProcessCommand(
		std::string const & message,
		ProcessMap const & map
	);

	void Respond(
		std::string const & username, 
		std::string const & body,
		REST::ResponseCallback callback
	);

	void ResponseHandler(REST::Response response);

};

#endif
