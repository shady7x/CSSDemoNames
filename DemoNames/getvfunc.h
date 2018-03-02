#pragma once

inline const void** getvtable(const void* t, unsigned int fs = 0)
{
	return *reinterpret_cast<const void***>((unsigned int)t + fs);
}

template<typename fn>
inline fn getvfunc(const void* t, unsigned int i, unsigned int fs = 0)
{
	return reinterpret_cast<fn>(getvtable(t, fs)[i]);
}