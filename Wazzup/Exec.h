#ifndef EXEC_H
#define EXEC_H

#include "Base.h"

namespace Exec {
	Process Create();
	void Destroy();

	std::string Run(std::string cmd);
}

#endif
