
#include "dyn_lib.h"

bool DynLib::Load()
{
    std::string strLibPath = "./";
    strLibPath += mstrName;
    mInst = (DYNLIB_HANDLE)DYNLIB_LOAD(strLibPath.c_str());

    return mInst != NULL;
}

bool DynLib::UnLoad()
{
    DYNLIB_UNLOAD(mInst);
    return true;
}

void* DynLib::GetSymbol(const char* szProcName)
{
    return (DYNLIB_HANDLE)DYNLIB_GETSYM(mInst, szProcName);
}
