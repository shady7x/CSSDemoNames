#pragma once

#include <string>
#include <map>
#include "sdk.h"

#define CCSPlayerResource 28
#define CSMAX_CLIENTS 65

namespace demonames 
{
	void clean_player_resources(int index);
	void list();
	bool continue_input();

	extern std::map <int, std::string> table;
	extern bool hide_avatars;
	extern bool hide_clantags;
}