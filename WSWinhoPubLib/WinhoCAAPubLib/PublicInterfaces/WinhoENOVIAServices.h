#ifdef  _WINDOWS_SOURCE
#ifdef  __WinhoENOVIAServices
#define ExportedByWinhoENOVIAServices     __declspec(dllexport)
#else
#define ExportedByWinhoENOVIAServices     __declspec(dllimport)
#endif
#else
#define ExportedByWinhoENOVIAServices
#endif
