#ifdef  _WINDOWS_SOURCE
#ifdef  __WinhoVisualServices
#define ExportedByWinhoVisualServices     __declspec(dllexport)
#else
#define ExportedByWinhoVisualServices     __declspec(dllimport)
#endif
#else
#define ExportedByWinhoVisualServices
#endif
