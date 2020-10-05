
#include "../../axis/axis.h"
#include "../world/world.h"

class __minecraft {
public:
	size_t address = NULL;
	bool _get_obj();
	void _get_data();
	bool is_in_menu();

};

namespace axis {

	extern std::shared_ptr<__minecraft> minecraft;

}