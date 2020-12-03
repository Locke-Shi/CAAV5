#ifdef  _WINDOWS_SOURCE
#ifdef  __WinhoCGMServices
#define ExportedByWinhoCGMServices     __declspec(dllexport)
#else
#define ExportedByWinhoCGMServices     __declspec(dllimport)
#endif
#else
#define ExportedByWinhoCGMServices
#endif
