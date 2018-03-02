﻿#include "vmt.h"
#include "demonames.h"
#include "console.h"

CEngine* g_pEngine;
CEntList* g_pEntList;
CVMTHookManager* g_pEngineHook;

CreateInterface_t EngineFactory, ClientFactory;

typedef bool(__thiscall* GetPlayerInfoFn)(void*, int, player_info_t*);
GetPlayerInfoFn oGetPlayerInfo;

bool __fastcall hkGetPlayerInfo(void* ecx, void* edx, int ent_id, player_info_t *info) 
{
	bool rt = oGetPlayerInfo(ecx, ent_id, info);

	std::map<int, std::string>::iterator it = demonames::table.find(ent_id);
	if (it != demonames::table.end())
		strcpy(info->name, it->second.c_str());
	if (demonames::hide_avatars)
		info->friendsID = 0;

	return rt; 
} 

DWORD WINAPI DllAttach(LPVOID hInst)
{
	EngineFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface");
	ClientFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("client.dll"), "CreateInterface");
	g_pEngine = (CEngine*)EngineFactory("VEngineClient013", 0); // bruteforce/find this and should work for V34/GO as well
	g_pEntList = (CEntList*)ClientFactory("VClientEntityList003", 0);

	if (g_pEntList && g_pEntList)
	{
		g_pEngineHook = new CVMTHookManager((PDWORD*)g_pEngine);
		oGetPlayerInfo = (GetPlayerInfoFn)g_pEngineHook->dwHookMethod((DWORD)hkGetPlayerInfo, 8);
		demonames::list();
	}

	console.destroy();
	g_pEngineHook->UnHook();
	Sleep(125);
	FreeLibraryAndExitThread(static_cast<HINSTANCE>(hInst), 0);
} 

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwR, LPVOID lpR)
{
	if (dwR == DLL_PROCESS_ATTACH)
	{
		console.setup();
		DisableThreadLibraryCalls(hInst);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DllAttach, hInst, 0, 0);
	}
	return TRUE;
}
