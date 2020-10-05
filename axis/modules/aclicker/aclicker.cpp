
#include "../modules.h"

float aclicker::cps = 10.f;

void aclicker::handler() {

	for (; "aclicker"; Sleep(1)) {

		if (!axis::minecraft->address || !axis::current_world->address ||
			!axis::local_player->address || axis::minecraft->is_in_menu()) continue;

		static size_t counter; counter++;
		float delay = (1000 / aclicker::cps) / 2;

		if (!axis::_is_pressed(VK_LBUTTON) || axis::_is_pressed(VK_RBUTTON)) { Sleep(delay * 2); continue; }

		if ((size_t)axis::_rand_val(1., 25.) == 1 && counter >= 5) { delay *= axis::_rand_val(0.90f, 0.95f); ++counter; }
		else if ((size_t)axis::_rand_val(1, 50.) == (size_t)5. && counter >= 3) { Sleep(delay * 1); counter = 0; }
		else if ((size_t)axis::_rand_val(1, 50.) == (size_t)5. && counter >= 3) { Sleep(delay * 2); counter = 0; }
		else if ((size_t)axis::_rand_val(1, 50.) == (size_t)5. && counter >= 3) { Sleep(delay * 2); counter = 0; }

		SendMessageW(GetForegroundWindow(), 0x201, MK_LBUTTON, MAKELPARAM(0, 0));
		Sleep(axis::_rand_val(delay, delay + axis::_rand_val(0.f, 2.f)));

		if ((size_t)axis::_rand_val(1., 25.) == 1 && counter >= 5) { delay *= axis::_rand_val(0.90f, 0.95f); ++counter; }
		else if ((size_t)axis::_rand_val(1, 50.) == (size_t)5. && counter >= 3) { Sleep(delay * 1); counter = 0; }
		else if ((size_t)axis::_rand_val(1, 50.) == (size_t)5. && counter >= 3) { Sleep(delay * 2); counter = 0; }
		else if ((size_t)axis::_rand_val(1, 50.) == (size_t)5. && counter >= 3) { Sleep(delay * 2); counter = 0; }

		SendMessageW(GetForegroundWindow(), 0x202, MK_LBUTTON, MAKELPARAM(0, 0));
		Sleep(axis::_rand_val(delay, delay + axis::_rand_val(0.f, 2.f)));

		if (counter >= 15) { counter = 0; Sleep(axis::_rand_val(delay, delay * 2)); }

	}

}