
#include "player.h"

std::shared_ptr<__player> axis::local_player = NULL;

void __player::set_address(size_t address) {

    this->address = address;

}

vec3 __player::get_pos() {

    vec3 pos;

    size_t field = this->address + 24;
    ZwReadVirtualMemory(axis::p_handle, (LPVOID)field, &pos, 24, 0);

    return pos;

}

float __player::get_yaw() {

    float yaw;

    size_t field = this->address + 136;

    ZwReadVirtualMemory(axis::p_handle, (LPVOID)field, &yaw, 4, 0);

    return yaw;


}

void __player::set_yaw(float yaw) {

    size_t field = this->address + 136;

    ZwWriteVirtualMemory(axis::p_handle, (LPVOID)field, &yaw, 4, 0);

}

float __player::get_pitch() {

    float pitch;

    size_t field = this->address + 140;

    ZwReadVirtualMemory(axis::p_handle, (LPVOID)field, &pitch, 4, 0);

    return pitch;


}

float __player::get_previous_yaw() {

    float yaw;

    size_t field = this->address + 144;

    ZwReadVirtualMemory(axis::p_handle, (LPVOID)field, &yaw, 4, 0);

    return yaw;


}

void __player::set_previous_yaw(float yaw) {

    size_t field = this->address + 144;

    ZwWriteVirtualMemory(axis::p_handle, (LPVOID)field, &yaw, 4, 0);

}

void __player::set_pitch(float pitch) {

    size_t field = this->address + 140;

    ZwWriteVirtualMemory(axis::p_handle, (LPVOID)field, &pitch, 4, 0);

}

float __player::get_previous_pitch() {

    float pitch;

    size_t field = this->address + 148;

    ZwReadVirtualMemory(axis::p_handle, (LPVOID)field, &pitch, 4, 0);

    return pitch;


}

void __player::set_previous_pitch(float pitch) {

    size_t field = this->address + 148;

    ZwWriteVirtualMemory(axis::p_handle, (LPVOID)field, &pitch, 4, 0);

}

vec3 __player::get_motion() {

    vec3 motion;
    
    size_t field = this->address + 72;
    ZwReadVirtualMemory(axis::p_handle, (LPVOID)field, &motion, 24, 0);

    return motion;

}

void __player::set_motion(vec3 motion) {

    size_t field = this->address + 72;
    ZwWriteVirtualMemory(axis::p_handle, (LPVOID)field, &motion, 24, 0);

}

int __player::get_hurt_timer() {

    int hurt_timer;
    size_t field = NULL;

    switch (axis::mc_version)
    {

    case V_189:
        field = this->address + 200;
        break;

    case V_1710:
        field = this->address + 208;
        break;

    }

    ZwReadVirtualMemory(axis::p_handle, (LPVOID)field, &hurt_timer, 4, 0);

    return hurt_timer;

}