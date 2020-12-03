#ifdef  _WINDOWS_SOURCE
#ifdef  __WinhoAgentServices
#define ExportedByWinhoAgentServices     __declspec(dllexport)
#else
#define ExportedByWinhoAgentServices     __declspec(dllimport)
#endif
#else
#define ExportedByWinhoAgentServices
#endif
