#pragma once

#include <string>
#include <map>
#include "sdk.h"

namespace demonames {
	void list();
	bool continue_input();
	extern std::map <int, std::string> table;
	extern bool hide_avatars;
};