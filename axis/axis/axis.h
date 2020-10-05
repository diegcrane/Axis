
#include <windows.h>
#include <vector>
#include <random>
#include <fstream>
#include <iostream>
#pragma comment(lib, "ntdll.lib")

#define VAR_TYPE unsigned int
#define RAND 300
#define V_1710 1
#define V_189 10
#define M_PI 3.1415926535897f
#define NT_SUCCESS(function) ((NTSTATUS)(function) >= NULL)

extern "C" NTSTATUS ZwReadVirtualMemory(HANDLE, PVOID, PVOID, SIZE_T, SIZE_T*);
extern "C" NTSTATUS ZwWriteVirtualMemory(HANDLE, PVOID, PVOID, SIZE_T, SIZE_T*);
extern "C" NTSTATUS ZwSetTimerResolution(ULONG, BOOLEAN, PULONG);

namespace axis {

	extern HANDLE p_handle;
	extern bool _open_mc();
	extern void _get_ver();
	extern void _handler();
	extern byte mc_version;
	extern size_t mc_c_ptr;
	extern bool mc_is_bdln;
	extern bool mc_is_cbrk;
	extern float mc_msense;

}

namespace axis {

	extern void _thread(void* x);
	extern bool _is_pressed(byte x);
	extern float _rand_val(float min, float max);
	extern void _vec_sort(std::vector<double> &v);
	extern bool _in_range(double x, double y, double z);
	extern bool _get_window_proc_id(const char* x, DWORD* pid);
	extern bool _get_process_handle(DWORD pid, HANDLE* handle);
	extern bool _is_foreground_window(const char* window_name);

}
