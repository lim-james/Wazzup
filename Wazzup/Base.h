#ifndef BASE_H
#define BASE_H

#include <map>
#include <string>
#include <functional>

typedef std::function<void(std::string)> Process;
typedef std::map<unsigned, Process> ProcessMap;

#endif
