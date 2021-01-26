#ifndef REST_H
#define REST_H

#include <Windows.h>
#include <string>
#include <vector>

namespace REST {
	struct Response {
		bool isSuccessful;
		std::wstring header;
		std::string body;
		std::vector<BYTE> rawBody;
	};

	std::string GetStr(std::vector<BYTE> const & arr);

	Response SendRequest(
		std::wstring const & domain, 
		std::wstring const & path, 
		std::wstring const & method
	);

	Response SendRequest(
		std::wstring const & domain,
		std::wstring const & path,
		std::wstring const & method,
		std::string const & body
	);

	Response SendRequest(
		std::wstring const & domain, 
		std::wstring const & path, 
		std::wstring const & method, 
		void * body, 
		DWORD bodySize
	);
};

#endif