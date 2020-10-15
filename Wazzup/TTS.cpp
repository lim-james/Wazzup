#include "TTS.h"

#include "Helpers.h"

Process TTS::Create() {
	ISpVoice* pVoice = nullptr;

	if (FAILED(::CoInitialize(nullptr))) {
		return nullptr;
	}

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	if (FAILED(hr)) {
		::CoUninitialize();
		return nullptr;
	}

	return std::bind(Speak, pVoice, std::placeholders::_1);
}

void TTS::Destroy() {
	::CoUninitialize();
}

void TTS::Speak(ISpVoice * voice, std::string content) {
	voice->Speak(Helpers::ToUTF16(content, CP_UTF8).c_str(), 0, NULL);
}
