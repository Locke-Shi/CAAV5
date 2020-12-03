#ifdef  _WINDOWS_SOURCE
#ifdef  __WinhoPPRServices
#define ExportedByWinhoPPRServices     __declspec(dllexport)
#else
#define ExportedByWinhoPPRServices     __declspec(dllimport)
#endif
#else
#define ExportedByWinhoPPRServices
#endif
