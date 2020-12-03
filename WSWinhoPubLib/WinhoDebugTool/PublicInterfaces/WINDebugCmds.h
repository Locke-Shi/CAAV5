#ifdef  _WINDOWS_SOURCE
#ifdef  __WINDebugCmds
#define ExportedByWINDebugCmds     __declspec(dllexport)
#else
#define ExportedByWINDebugCmds     __declspec(dllimport)
#endif
#else
#define ExportedByWINDebugCmds
#endif
