#include "JDAIPTRoot.h"

#ifndef LOCAL_DEFINITION_FOR_IID
IID IID_JDAIPTRoot = { 0xaa09b6f4, 0x5043, 0x4ad9, { 0x94, 0x93, 0x67, 0x62, 0xd3, 0x89, 0x65, 0x80} };
#endif

CATImplementInterface(JDAIPTRoot, CATBaseUnknown);
CATImplementHandler(JDAIPTRoot, CATBaseUnknown);