#pragma once
#ifdef CREATE_EXPORTS
#define DLL_TYPE __declspec(dllexport)
#else
#define DLL_TYPE __declspec(dllimport)
#endif

extern "C" DLL_TYPE int add(int x, int y);