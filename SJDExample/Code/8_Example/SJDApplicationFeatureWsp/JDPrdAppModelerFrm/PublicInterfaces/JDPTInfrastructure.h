#ifdef  _WINDOWS_SOURCE
#ifdef  __JDPTInfrastructure
#define ExportedByJDPTInfrastructure     __declspec(dllexport)
#else
#define ExportedByJDPTInfrastructure     __declspec(dllimport)
#endif
#else
#define ExportedByJDPTInfrastructure
#endif
