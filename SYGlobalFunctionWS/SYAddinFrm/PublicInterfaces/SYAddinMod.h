#ifdef  _WINDOWS_SOURCE
#ifdef  __SYAddinMod
#define ExportedBySYAddinMod     __declspec(dllexport)
#else
#define ExportedBySYAddinMod     __declspec(dllimport)
#endif
#else
#define ExportedBySYAddinMod
#endif
