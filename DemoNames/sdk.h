#pragma once
#pragma optimize("gsy", on)

#include <windows.h>
#include <math.h>
#include "getvfunc.h"
#include <iostream>

typedef void* (__cdecl* CreateInterface_t)(const char*, int*);
typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);

typedef struct player_info_s
{
	char		    name[32];
	int             userID; 
	char            guid[33];
	unsigned long   friendsID;
	char            friendsName[32];
	bool            fakeplayer;
	bool            ishltv;
	unsigned long   customFiles[4];
	unsigned char   filesDownloaded;
} player_info_t;

class CEngine
{
public:
	bool GetPlayerInfo(int ent_id, player_info_t* info)
	{
		typedef bool(__thiscall* fn)(void*, int, player_info_t*);
		return getvfunc<fn>(this, 8)(this, ent_id, info);
	}
	int GetMaxClients()
	{
		typedef int(__thiscall* fn)(void*);
		return getvfunc<fn>(this, 21)(this);
	}
};

class ClientClass
{
public:
	int GetClassID()
	{
		return *reinterpret_cast<int*>((uintptr_t)this + 0x14);
	}
};

class CBaseEntity
{
public:
	ClientClass* GetClientClass() {
		void* pNetworkable = (void*)(this + 0x8);
		typedef ClientClass*(__thiscall* fn)(void*);
		return getvfunc<fn>(pNetworkable, 2)(pNetworkable);
	}
};

class CEntList
{
public:
	CBaseEntity* GetClientEntity(int ent_id)
	{
		typedef CBaseEntity*(__thiscall* fn)(void*, int);
		return getvfunc<fn>(this, 3)(this, ent_id);
	}
	int GetHighestEntityIndex()
	{
		typedef int(__thiscall* fn)(void*);
		return getvfunc<fn>(this, 6)(this);
	}
};

extern CEntList* g_pEntList;
extern CEngine* g_pEngine;