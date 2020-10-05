
#include "../axis/axis.h"

bool axis::_is_pressed(byte x) {

	return GetAsyncKeyState(x)&0x8000;

}

void axis::_thread(void* x) {

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)x, 0, 0, 0);

}

float axis::_rand_val(float min, float max) {

	++max;
	std::random_device device;
	std::mt19937 engine(device());
	std::uniform_real_distribution<> random_value(min, max);
	return (float)random_value(engine);

}

void axis::_vec_sort(std::vector<double>& v) {

	for (size_t i = 0; i < v.size(); i++) {

		for (size_t j = i + 1; j < v.size(); j++) {

			if (v[i] > v[j]) {

				double x = v[i];
				v[i] = v[j];
				v[j] = x;
			}

		}

	}

}

bool axis::_in_range(double x, double y, double z) {

	if (y > z) {

		if (x > y) return false;
		if (x < z) return false;
		return true;

	}

	if (z > y) {

		if (x > z) return false;
		if (x < y) return false;
		return true;

	}

	return false;

}

bool axis::_get_window_proc_id(const char* x, DWORD* pid) {

	HWND wind = FindWindowA(x, nullptr);
	if (wind) {
	
		GetWindowThreadProcessId(wind, pid);

	}

	return (bool)*pid;

}

bool axis::_get_process_handle(DWORD pid, HANDLE* handle) {

	*handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	return (bool)*handle;

}

bool axis::_is_foreground_window(const char* window_name) {

	return GetForegroundWindow() == FindWindowA(window_name, nullptr);

}