#include "REST.h"

#include <winhttp.h>
#include <cstdio>

#pragma comment(lib, "winhttp.lib")

std::string REST::GetStr(std::vector<BYTE> const & arr) {
	std::string result = "";

	for (BYTE b : arr)
		result += b;

	return result;
}

REST::Response REST::SendRequest(
	std::wstring const & domain,
	std::wstring const & path,
	std::wstring const & method
) {
	return SendRequest(domain, path, method, nullptr, 0);
}

REST::Response REST::SendRequest(
	std::wstring const & domain,
	std::wstring const & path,
	std::wstring const & method,
	std::string const & body
) {
	return SendRequest(
		domain,
		path,
		method,
		(void*)body.c_str(),
		body.size()
	);
}

REST::Response REST::SendRequest(
	std::wstring const & domain, 
	std::wstring const & path, 
	std::wstring const & method, 
	void *body, 
	DWORD bodySize
) {
	Response response;

	DWORD dwSize;
	DWORD dwDownloaded;
	DWORD headerSize = 0;
	BOOL  bResults = FALSE;
	HINTERNET hSession = nullptr;
	HINTERNET hConnect = nullptr;
	HINTERNET hRequest = nullptr;

	hSession = WinHttpOpen(L"Example UserAgent/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	if (hSession)
		hConnect = WinHttpConnect(hSession, domain.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
	else
		printf("session handle failed\n");

	if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect, method.c_str(), path.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
	else
		printf("connect handle failed\n");

	if (hRequest)
		bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, body, bodySize, bodySize, 0);
	else
		printf("request handle failed\n");

	if (bResults) 
		bResults = WinHttpReceiveResponse(hRequest, NULL);

	if (bResults)
	{
		bResults = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, NULL, WINHTTP_NO_OUTPUT_BUFFER, &headerSize, WINHTTP_NO_HEADER_INDEX);
		if ((!bResults) && (GetLastError() == ERROR_INSUFFICIENT_BUFFER))
		{
			response.header.resize(headerSize / sizeof(wchar_t));
			if (response.header.empty())
			{
				bResults = TRUE;
			}
			else
			{
				bResults = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, NULL, &response.header[0], &headerSize, WINHTTP_NO_HEADER_INDEX);
				if (!bResults) headerSize = 0;
				response.header.resize(headerSize / sizeof(wchar_t));
			}
		}
	}

	if (bResults)
	{
		do
		{
			// Check for available data.
			dwSize = 0;
			bResults = WinHttpQueryDataAvailable(hRequest, &dwSize);
			if (!bResults)
			{
				printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());
				break;
			}

			if (dwSize == 0)
				break;

			do
			{
				// Allocate space for the buffer.
				DWORD dwOffset = response.rawBody.size();
				response.rawBody.resize(dwOffset + dwSize);

				// Read the data.
				bResults = WinHttpReadData(hRequest, &response.rawBody[dwOffset], dwSize, &dwDownloaded);
				if (!bResults)
				{
					printf("Error %u in WinHttpReadData.\n", GetLastError());
					dwDownloaded = 0;
				}

				response.rawBody.resize(dwOffset + dwDownloaded);

				if (dwDownloaded == 0)
					break;

				dwSize -= dwDownloaded;
			} while (dwSize > 0);
		} while (true);
	}

	// Report any errors.
	if (!bResults)
		printf("Error %d has occurred.\n", GetLastError());

	// Close any open handles.
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);

	response.isSuccessful = bResults;
	response.body = GetStr(response.rawBody);

	return response;
}
