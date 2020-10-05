
#include "minecraft.h"

std::shared_ptr<__minecraft> axis::minecraft = NULL;

bool __minecraft::_get_obj() {

    VAR_TYPE c_addr, o_addr;

    ZwReadVirtualMemory(axis::p_handle, (LPVOID)axis::mc_c_ptr, &c_addr, sizeof(VAR_TYPE), 0);

    c_addr += 120;

    ZwReadVirtualMemory(axis::p_handle, (LPVOID)(size_t)c_addr, &o_addr, sizeof(VAR_TYPE), 0);

    this->address = o_addr;

    return (bool)this->address;

}

void __minecraft::_get_data() {

    VAR_TYPE world;
    size_t world_field = NULL;

    switch (axis::mc_version)
    {

    case V_189:
        world_field = this->address + 148;
        if (axis::mc_is_bdln) world_field = this->address + 164;
        break;

    case V_1710:
        world_field = this->address + 124;
        if (axis::mc_is_bdln) world_field = this->address + 144;
        if (axis::mc_is_cbrk) world_field = this->address + 132;
        break;

    }

    ZwReadVirtualMemory(axis::p_handle, (LPVOID)world_field, &world, sizeof(VAR_TYPE), 0);

    axis::current_world->set_address((size_t)world);

    VAR_TYPE player;
    size_t player_field = NULL;

    switch (axis::mc_version)
    {

    case V_189:
        player_field = this->address + 168;
        if (axis::mc_is_bdln) player_field = this->address + 188;
        break;

    case V_1710:
        player_field = this->address + 132;
        if (axis::mc_is_bdln) player_field = this->address + 152;
        if (axis::mc_is_cbrk) player_field = this->address + 140;
        break;

    }

    ZwReadVirtualMemory(axis::p_handle, (LPVOID)player_field, &player, sizeof(VAR_TYPE), 0);

    axis::local_player->set_address((size_t)player);

    static bool sense_set;
    if (sense_set) return;

    char* appdata; _dupenv_s(&appdata, nullptr, "APPDATA");
    std::string opt = (std::string)appdata + "\\.minecraft\\options.txt";

    std::ifstream options_content(opt);
    std::string opt_str((std::istreambuf_iterator<char>(options_content))
        , std::istreambuf_iterator<char>());

    std::string current_line;
    for (size_t it = 0; it < opt_str.length(); ++it) {

        if (opt_str[it] != '\n') {

            current_line.push_back(opt_str[it]);

        } else {

            if (current_line.find("mouseSensitivity:") != std::string::npos) {

                std::string sense = current_line.substr(current_line.find(":") + 1);
                axis::mc_msense = atof(sense.c_str());

            }

            current_line = "";

        }

    }

    sense_set = true;

}

bool __minecraft::is_in_menu() {

    bool is_open;

    size_t inventory_field = NULL;
    
    switch (axis::mc_version)
    {

    case V_189:
        inventory_field = this->address + 102;
        if (axis::mc_is_bdln) inventory_field = this->address + 110;
        break;

    case V_1710:
        inventory_field = this->address + 85;
        if (axis::mc_is_bdln) inventory_field = this->address + 101;
        break;

    }

    ZwReadVirtualMemory(axis::p_handle, (LPVOID)inventory_field, &is_open, sizeof(bool), 0);

    return !is_open;

}