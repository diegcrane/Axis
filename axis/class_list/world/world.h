
#include "../../axis/axis.h"
#include "../player/player.h"

class __world {
public:
	size_t address = NULL;
	void set_address(size_t address);
	std::vector<size_t> get_player_list();

};

namespace axis {

	extern std::shared_ptr<__world> current_world;

}