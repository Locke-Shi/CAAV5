#ifdef  _WINDOWS_SOURCE
#ifdef  __WinhoMD5Services
#define ExportedByWinhoMD5Services     __declspec(dllexport)
#else
#define ExportedByWinhoMD5Services     __declspec(dllimport)
#endif
#else
#define ExportedByWinhoMD5Services
#endif
