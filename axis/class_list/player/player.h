
#include "../../axis/axis.h"
#include "../_vec3/vec3.h"

class __player {
public:
	size_t address = NULL;
	void set_address(size_t address);

	vec3 get_pos();

	float get_yaw();
	void set_yaw(float yaw);

	float get_previous_yaw();
	void set_previous_yaw(float yaw);

	float get_pitch();
	void set_pitch(float pitch);

	float get_previous_pitch();
	void set_previous_pitch(float pitch);

	vec3 get_motion();
	void set_motion(vec3 motion);

	int get_hurt_timer();

};

namespace axis {

	extern std::shared_ptr<__player> local_player;

}