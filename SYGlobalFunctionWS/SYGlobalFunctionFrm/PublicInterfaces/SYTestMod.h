#ifdef  _WINDOWS_SOURCE
#ifdef  __SYTestMod
#define ExportedBySYTestMod     __declspec(dllexport)
#else
#define ExportedBySYTestMod     __declspec(dllimport)
#endif
#else
#define ExportedBySYTestMod
#endif
