#ifndef BROWSER_H
#define BROWSER_H

#include "Base.h"

namespace Browser {

	Process Create();
	void Destroy();

	void Open(std::string content);
}

#endif
