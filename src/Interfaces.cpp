#include "Interfaces.h"
#include "utils/Logger.h"
#include "utils/Scanner.h"
#include "utils/Memutils.h"

// InterfaceInternal
// 48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC ?? 48 8B 1D ?? ?? ?? ?? 48 8B FA 48


typedef void* (*InstantiateInterfaceFn) ();

struct InterfaceReg
{
    InstantiateInterfaceFn m_CreateFn;
    const char *m_pName;
    InterfaceReg *m_pNext;
};

void Interfaces::FindInterfaces( WinProcess &process, const char *moduleName ) {
    uintptr_t createInterfaceFunc = Scanner::FindPatternInModule( "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC ?? 48 8B 1D ?? ?? ?? ?? 48 8B FA 48", moduleName, process );
    Logger::Log("CreateInterfaceFunc: %p\n", (void*)createInterfaceFunc);
    uintptr_t interfaceList = GetAbsoluteAddressVm( process, createInterfaceFunc + 20, 3, 7 );
    Logger::Log("Interface list: %p\n", (void*)interfaceList);

}