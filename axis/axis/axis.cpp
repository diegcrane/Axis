
#include "axis.h"
#include "../modules/modules.h"

HANDLE axis::p_handle = NULL;
byte axis::mc_version = NULL;
size_t axis::mc_c_ptr = NULL;
bool axis::mc_is_bdln = NULL;
bool axis::mc_is_cbrk = NULL;
float axis::mc_msense = 0.5f;

bool axis::_open_mc() {
    
    DWORD proc_id;
    if (!axis::_get_window_proc_id("LWJGL", &proc_id)) {
     
        return false;
    
    }

    HANDLE* proc_hdl = &axis::p_handle;
    if (!axis::_get_process_handle(proc_id, proc_hdl)) {

        return false;

    }

    return true;

}

void axis::_get_ver() {

    for (size_t adrs = 0x0; adrs < 0xffffffff; adrs += 100000) {

        std::string memory; memory.resize(100000);

        if (!NT_SUCCESS(ZwReadVirtualMemory(axis::p_handle, (LPVOID)adrs, &memory[0], 100000, 0))) 
            continue;
    
        if (memory.find("Badlion") != std::string::npos) axis::mc_is_bdln = true;
        if (memory.find("CheatBreaker") != std::string::npos) axis::mc_is_cbrk = true;

        if (!axis::mc_version) {

            if (memory.find("1.8.9") != std::string::npos)  axis::mc_version = V_189;
            if (memory.find("1.7.10") != std::string::npos) axis::mc_version = V_1710;

        } else break;

    }

}

void axis::_handler() {

    ULONG current_resolution;
    ZwSetTimerResolution(1, true, &current_resolution);

    for (
        axis::minecraft = std::make_shared<__minecraft>(),
        axis::current_world = std::make_shared<__world>(),
        axis::local_player = std::make_shared<__player>(),
        axis::_thread(aclicker::handler),
        axis::_thread(aim::handler),
        axis::_thread(velocity::handler);; Sleep((int)50))
    { 
        
        if (minecraft->_get_obj()) minecraft->_get_data();

    }

}