#ifdef  _WINDOWS_SOURCE
#ifdef  __SYGlobalFunctionMod
#define ExportedBySYGlobalFunctionMod     __declspec(dllexport)
#else
#define ExportedBySYGlobalFunctionMod     __declspec(dllimport)
#endif
#else
#define ExportedBySYGlobalFunctionMod
#endif
