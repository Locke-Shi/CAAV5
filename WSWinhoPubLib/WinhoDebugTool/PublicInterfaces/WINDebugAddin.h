#ifdef  _WINDOWS_SOURCE
#ifdef  __WINDebugAddin
#define ExportedByWINDebugAddin     __declspec(dllexport)
#else
#define ExportedByWINDebugAddin     __declspec(dllimport)
#endif
#else
#define ExportedByWINDebugAddin
#endif
