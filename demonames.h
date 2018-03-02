#pragma once

#include <string>
#include <map>

extern std::map <int, std::string> nametable;

namespace demonames {
	void list();
	bool continue_input();
	extern bool hide_avatars;
};