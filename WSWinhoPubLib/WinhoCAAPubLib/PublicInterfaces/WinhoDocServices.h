#ifdef  _WINDOWS_SOURCE
#ifdef  __WinhoDocServices
#define ExportedByWinhoDocServices     __declspec(dllexport)
#else
#define ExportedByWinhoDocServices     __declspec(dllimport)
#endif
#else
#define ExportedByWinhoDocServices
#endif
