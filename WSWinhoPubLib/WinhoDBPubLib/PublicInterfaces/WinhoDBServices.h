#ifdef  _WINDOWS_SOURCE
#ifdef  __WinhoDBServices
#define ExportedByWinhoDBServices     __declspec(dllexport)
#else
#define ExportedByWinhoDBServices     __declspec(dllimport)
#endif
#else
#define ExportedByWinhoDBServices
#endif
