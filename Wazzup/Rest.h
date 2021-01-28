#ifndef REST_H
#define REST_H

#include <Windows.h>
#include <string>
#include <vector>
#include <functional>

namespace REST {
	struct Response {
		bool isSuccessful;
		std::wstring header;
		std::string body;
		std::vector<BYTE> rawBody;
	};

	typedef std::function<void(Response)> ResponseCallback;

	std::string GetStr(std::vector<BYTE> const & arr);

	Response SendRequest(
		std::wstring const & domain, 
		std::wstring const & path, 
		std::wstring const & method
	);

	void SendRequestAsync(
		std::wstring const & domain, 
		std::wstring const & path, 
		std::wstring const & method,
		ResponseCallback callback
	);

	Response SendRequest(
		std::wstring const & domain,
		std::wstring const & path,
		std::wstring const & method,
		std::string const & body
	);

	void SendRequestAsync(
		std::wstring const & domain, 
		std::wstring const & path, 
		std::wstring const & method,
		std::string const & body,
		ResponseCallback callback
	);

	Response SendRequest(
		std::wstring const & domain, 
		std::wstring const & path, 
		std::wstring const & method, 
		void * body, 
		DWORD bodySize
	);

	void SendRequestAsync(
		std::wstring const & domain, 
		std::wstring const & path, 
		std::wstring const & method,
		void * body, 
		DWORD bodySize,
		ResponseCallback callback
	);

};

#endif