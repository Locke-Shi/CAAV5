#ifdef  _WINDOWS_SOURCE
#ifdef  __JDAPTObjectView
#define ExportedByJDAPTObjectView     __declspec(dllexport)
#else
#define ExportedByJDAPTObjectView     __declspec(dllimport)
#endif
#else
#define ExportedByJDAPTObjectView
#endif
