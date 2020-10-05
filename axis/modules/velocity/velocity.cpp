
#include "../modules.h"

double velocity::velocity_h = 1.;
double velocity::velocity_v = 1.;

void velocity::handler() {

	for (static bool motion_set; "velocity"; Sleep(1)) {

		if (!axis::minecraft->address || !axis::current_world->address ||
			!axis::local_player->address) continue;

		vec3 motion = axis::local_player->get_motion();
		static vec3 _motion_ = { 0.0, 0.0, 0.0 };

		if (motion.y >= 9. || motion.y <= -9 || isnan(motion.y)) continue;

		if (!motion_set && axis::local_player->get_hurt_timer() >= 19) {

			if (
				_motion_.x != motion.x ||
				_motion_.y != motion.y ||
				_motion_.z != motion.z
				) {

				axis::local_player->set_motion({
					motion.x * (velocity_h / 100.),
					motion.y * (velocity_v / 100.),
					motion.z * (velocity_h / 100.)
				});

				motion_set = true;

			}

		} else 
			if (motion_set && axis::local_player->get_hurt_timer() < 19)
				motion_set = false; _motion_ = motion;

	}

}
