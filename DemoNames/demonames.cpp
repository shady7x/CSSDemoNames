#include "demonames.h"

std::map <int, std::string> demonames::table;
bool demonames::hide_avatars;
bool demonames::hide_clantags;

void demonames::clean_player_resources(int index)
{
	CBaseEntity* resources = nullptr;
	for (int i = 1; i <= g_pEntList->GetHighestEntityIndex(); ++i)
	{
		CBaseEntity* entity = g_pEntList->GetClientEntity(i);
		if (entity == nullptr || entity->GetClientClass()->GetClassID() != CCSPlayerResource)
			continue;
		resources = entity;
		break;
	}
	if (resources)
		strcpy(reinterpret_cast<char*>((uintptr_t)resources + 0xED8 + index * 16), "");
}

void demonames::list()
{
	do { 
		system("cls");
		std::cout << "ID     Name\n";
		for (int i = 0; i < 12; ++i)
			std::cout << '-';
		std::cout << std::endl;

		for (int i = 1; i <= g_pEngine->GetMaxClients(); ++i)
		{
			player_info_s info;
			if (!g_pEntList->GetClientEntity(i) || !g_pEngine->GetPlayerInfo(i, &info))
				continue;

			std::cout << i;
			for (int j = 0; j < (i < 10 ? 5 : 4); ++j)
				std::cout << ' ';
			std::cout << info.name << std::endl;
		}

		for (int i = 0; i < 12; ++i)
			std::cout << '-';
		std::cout << std::endl;

	} while (continue_input());
}

bool demonames::continue_input()
{
	int id;
	std::cin >> id;
	if (id < 0)
	{
		return false;
	}
	if (!id)
	{
		return true;
	}

	std::string cmd;
	std::cin >> cmd;

	if (cmd == "->")
	{
		if (id == 1111)
		{
			return hide_avatars = true;
		}
		if (id == 2222)
		{
			return hide_clantags = true;
		}
		std::string newname;
		std::getline(std::cin, newname);
		newname.erase(0, 1);
		if (id == 111)
		{
			for (int i = 1; i <= CSMAX_CLIENTS; ++i)
				table[i] = newname;
		}
		else
		{
			table[id] = newname;
		}
	}

	if (cmd == "<-")
	{
		if (id == 1111)
		{
			return hide_avatars = false, true;
		}
		else if (id == 2222)
		{
			return hide_clantags = false, true;  
		}
		else if (id == 111)
		{
			table.clear();
		}
		else for (std::map<int, std::string>::iterator it = table.begin(); it != table.end(); )
		{
			if (it->first == id)
				it = table.erase(it);
			else
				++it;
		}
	}

	return true;
}