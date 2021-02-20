#ifdef  _WINDOWS_SOURCE
#ifdef  __JDAPTObjects
#define ExportedByJDAPTObjects     __declspec(dllexport)
#else
#define ExportedByJDAPTObjects     __declspec(dllimport)
#endif
#else
#define ExportedByJDAPTObjects
#endif
