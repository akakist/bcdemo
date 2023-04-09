#include "IInstance.h"

IUtils *iUtils;
void registerBlockchainNodeService(const char* pn);
extern "C" void
#ifdef _WIN32
__declspec(dllexport)
#endif
#ifdef DEBUG
registerModuleDebug
#else
registerModule
#endif
(IUtils* f,const char* pn)
{

    iUtils=f;
    registerBlockchainNodeService(pn);
}

