#ifdef  _WINDOWS_SOURCE
#ifdef  __JDAPTCommands
#define ExportedByJDAPTCommands     __declspec(dllexport)
#else
#define ExportedByJDAPTCommands     __declspec(dllimport)
#endif
#else
#define ExportedByJDAPTCommands
#endif
