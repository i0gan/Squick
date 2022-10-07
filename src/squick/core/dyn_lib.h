#ifndef SQUICK_DYNLIB_H
#define SQUICK_DYNLIB_H

#include <stdio.h>
#include <iostream>
#include "platform.h"


#include <dlfcn.h>
#define DYNLIB_HANDLE void*
#define DYNLIB_LOAD( a ) dlopen( a, RTLD_LAZY | RTLD_GLOBAL)
#define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#define DYNLIB_UNLOAD( a ) dlclose( a )

//struct HINSTANCE__;
//typedef struct HINSTANCE__* hInstance;


class DynLib
{

public:

    DynLib(const std::string& name) {
        mbMain = false;
        mstrName = "plugin/";
        mstrName.append(name);
        mstrName.append(".so");
#ifdef DEBUG
        printf("Load Plugin from :%s\n", mstrName.c_str());
#endif
    }

    ~DynLib()
    {
    }

    bool Load();

    bool UnLoad();

    /// Get the name of the library
    const std::string& GetName(void) const
    {
        return mstrName;
    }

    const bool GetMain(void) const
    {
        return mbMain;
    }

    void* GetSymbol(const char* szProcName);

protected:

    std::string mstrName;
    bool mbMain;

    DYNLIB_HANDLE mInst;
};

#endif
