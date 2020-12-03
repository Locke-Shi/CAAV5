#ifdef  _WINDOWS_SOURCE
#ifdef  __SJDPartExampleM
#define ExportedBySJDPartExampleM     __declspec(dllexport)
#else
#define ExportedBySJDPartExampleM     __declspec(dllimport)
#endif
#else
#define ExportedBySJDPartExampleM
#endif
