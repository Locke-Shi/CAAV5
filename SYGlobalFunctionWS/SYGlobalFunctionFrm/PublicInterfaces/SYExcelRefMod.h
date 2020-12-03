#ifdef  _WINDOWS_SOURCE
#ifdef  __SYExcelRefMod
#define ExportedBySYExcelRefMod     __declspec(dllexport)
#else
#define ExportedBySYExcelRefMod     __declspec(dllimport)
#endif
#else
#define ExportedBySYExcelRefMod
#endif
