#ifdef  _WINDOWS_SOURCE
#ifdef  __SJDRelinkDrawingPartM
#define ExportedBySJDRelinkDrawingPartM     __declspec(dllexport)
#else
#define ExportedBySJDRelinkDrawingPartM     __declspec(dllimport)
#endif
#else
#define ExportedBySJDRelinkDrawingPartM
#endif
