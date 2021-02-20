#ifdef  _WINDOWS_SOURCE
#ifdef  __JDAPTInfrastructureView
#define ExportedByJDAPTInfrastructureView     __declspec(dllexport)
#else
#define ExportedByJDAPTInfrastructureView     __declspec(dllimport)
#endif
#else
#define ExportedByJDAPTInfrastructureView
#endif
