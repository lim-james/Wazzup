#ifndef TTS_H
#define TTS_H

#include "Base.h"

#include <sapi.h>

namespace TTS {
	Process Create();
	void Destroy();

	std::string Speak(ISpVoice * pVoice, std::string content);
}

#endif
