#include "Guid.h"

TCHAR* Guid::data() const
{
    return guid;
}

Guid Guid::NewGuid()
{
    UUID id;

    if (RPC_S_OK != UuidCreate(&id))
        id = GUID_NULL;

    TCHAR sId[129];
    wchar_t swId[129];

    int r = ::StringFromGUID2(id, swId, 128);
    ::wcstombs((char*)sId, swId, 128);

    return Guid();
}
