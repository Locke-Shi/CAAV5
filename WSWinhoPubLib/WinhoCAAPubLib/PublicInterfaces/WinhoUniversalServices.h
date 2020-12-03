#ifdef  _WINDOWS_SOURCE
#ifdef  __WinhoUniversalServices
#define ExportedByWinhoUniversalServices     __declspec(dllexport)
#else
#define ExportedByWinhoUniversalServices     __declspec(dllimport)
#endif
#else
#define ExportedByWinhoUniversalServices
#endif
