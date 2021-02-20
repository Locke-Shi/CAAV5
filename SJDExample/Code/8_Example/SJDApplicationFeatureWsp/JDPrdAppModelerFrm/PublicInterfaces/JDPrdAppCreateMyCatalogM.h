#ifdef  _WINDOWS_SOURCE
#ifdef  __JDPrdAppCreateMyCatalogM
#define ExportedByJDPrdAppCreateMyCatalogM     __declspec(dllexport)
#else
#define ExportedByJDPrdAppCreateMyCatalogM     __declspec(dllimport)
#endif
#else
#define ExportedByJDPrdAppCreateMyCatalogM
#endif
