#pragma once
#pragma optimize("gsy", on)

#include <windows.h>
#include <math.h>
#include "getvfunc.h"
#include <iostream>

typedef void* (__cdecl* CreateInterface_t)(const char*, int*);
typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

typedef struct player_info_s
{
	char			name[32];
	int				userID; 
	char			guid[33];
	unsigned long	friendsID;
	char			friendsName[32];
	bool			fakeplayer;
	bool			ishltv;
	unsigned long	customFiles[4];
	unsigned char	filesDownloaded;
} player_info_t;

class CEngine
{
public:
	bool GetPlayerInfo(int ent_id, player_info_t* info)
	{
		typedef bool(__thiscall* fn)(PVOID, int, player_info_t*);
		return getvfunc<fn>(this, 8)(this, ent_id, info);
	}
	int GetMaxClients()
	{
		typedef int(__thiscall* fn)(PVOID);
		return getvfunc<fn>(this, 21)(this);
	}
};

class CEntList
{
public:
	void* GetClientEntity(int ent_id)
	{
		typedef void* (__thiscall* fn)(PVOID, int);
		return getvfunc<fn>(this, 3)(this, ent_id);
	}
};

extern CEntList* g_pEntList;
extern CEngine* g_pEngine;