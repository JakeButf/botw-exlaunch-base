#include "lib.hpp"
#include "inputs.h"

extern "C" void exl_main(void* x0, void* x1) {
    // Setup hooking enviroment
    envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::hook::Initialize();

    //Init Hooks
    inputs::InitHooks();
    /*
    For sysmodules/applets, you have to call the entrypoint when ready
    exl::hook::CallTargetEntrypoint(x0, x1);
    */
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}