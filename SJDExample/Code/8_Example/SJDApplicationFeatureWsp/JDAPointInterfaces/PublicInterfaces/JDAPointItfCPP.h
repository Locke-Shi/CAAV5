#ifdef  _WINDOWS_SOURCE
#ifdef  __JDAPointItfCPP
#define ExportedByJDAPointItfCPP     __declspec(dllexport)
#else
#define ExportedByJDAPointItfCPP     __declspec(dllimport)
#endif
#else
#define ExportedByJDAPointItfCPP
#endif
