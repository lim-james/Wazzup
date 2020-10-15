#ifndef TTS_H
#define TTS_H

#include "Base.h"

#include <sapi.h>

namespace TTS {

	Process Create();
	void Destroy();

	void Speak(ISpVoice * pVoice, std::string content);

}

#endif
