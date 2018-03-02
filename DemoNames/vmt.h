#pragma once

#include <windows.h>

class CVMTHookManager 
{
public:
	CVMTHookManager() 
	{
		memset(this, 0, sizeof(CVMTHookManager));
	}
	CVMTHookManager(PDWORD* cBase) 
	{
		bInit(cBase);
	}
	~CVMTHookManager() 
	{
		UnHook();
	}
	bool bInit(PDWORD* ppdwClassBase) 
	{
		m_ppdwClassBase = ppdwClassBase;
		m_pdwOldVMT = *ppdwClassBase;
		m_dwVMTSize = getCnt(*ppdwClassBase);
		m_pdwNewVMT = new DWORD[m_dwVMTSize];
		memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(DWORD) * m_dwVMTSize);
		*ppdwClassBase = m_pdwNewVMT;
		return 1;
	}
	bool bInit(PDWORD** pBase) 
	{
		return bInit(*pBase);
	}
	void UnHook() 
	{
		if (m_ppdwClassBase) *m_ppdwClassBase = m_pdwOldVMT;
	}
	DWORD dwHookMethod(DWORD dwNewFunc, unsigned int ind) 
	{
		if (m_pdwNewVMT && m_pdwOldVMT && ind <= m_dwVMTSize && ind >= 0) {
			m_pdwNewVMT[ind] = dwNewFunc;
			return m_pdwOldVMT[ind];
		}
		return 0;
	}
private:
	DWORD getCnt(PDWORD pv) 
	{
		DWORD ind = 0;
		for (ind = 0; pv[ind]; ++ind) 
			if (IS_INTRESOURCE((FARPROC)pv[ind])) 
				break;
		return ind;
	}
	PDWORD*	m_ppdwClassBase, m_pdwNewVMT, m_pdwOldVMT;
	DWORD	m_dwVMTSize;
};