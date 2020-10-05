
#include "../modules.h"

float aim::max_angle = 180.f;
float aim::aim_speed = 10.0f;
float aim::aim_distance = 6.f;

void aim::handler() {

	for (; "aim"; Sleep(1)) {

		if (!axis::_is_pressed(VK_LBUTTON)) { Sleep(100); continue; }

		if (!axis::minecraft->address || !axis::current_world->address || 
			!axis::local_player->address || axis::minecraft->is_in_menu()) continue;

		size_t selectet_player = 0; double closest_yaw = 500.0;
		
		vec3 my_pos = axis::local_player->get_pos(); 

		float_t my_yaw = axis::local_player->get_yaw(), my_pyaw = axis::local_player->get_previous_yaw(),
		my_pitch = axis::local_player->get_pitch(), my_ppitch = axis::local_player->get_previous_pitch();

		for (size_t current : axis::current_world->get_player_list()) {

			auto current_player = std::make_shared<__player>(); current_player->set_address(current);

			vec3 cp_pos = current_player->get_pos();

			double distance = sqrt(pow(cp_pos.x - my_pos.x, 2) + pow(cp_pos.y - my_pos.y, 2) + pow(cp_pos.z - my_pos.z, 2)); 

			if (distance >= aim::aim_distance) continue;

			double distance_x = cp_pos.x - my_pos.x;
			double distance_z = cp_pos.z - my_pos.z;

			float dif = (float)atan2((float)distance_z, (float)distance_x) * 180.00f / M_PI - 90.00f;

			dif = fmodf(dif - my_yaw, 360.f);
			if (dif >= 180.0f) dif -= 360.0f;
			if (dif < -180.0f) dif += 360.0f;

			if (abs(dif) <= aim::max_angle && abs(dif) < abs(closest_yaw)) selectet_player = current, closest_yaw = dif;

		}

		if (closest_yaw != 500.0 && selectet_player) {

			auto crrent_p = std::make_shared<__player>(); crrent_p->set_address(selectet_player);

			vec3 cp_pos = crrent_p->get_pos(), crnr_1, crnr_2, crnr_3, crnr_4;

			crnr_1 = { cp_pos.x - 0.30f, cp_pos.y, cp_pos.z + 0.30f };
			crnr_2 = { cp_pos.x - 0.30f, cp_pos.y, cp_pos.z - 0.30f };
			crnr_3 = { cp_pos.x + 0.30f, cp_pos.y, cp_pos.z - 0.30f };
			crnr_4 = { cp_pos.x + 0.30f, cp_pos.y, cp_pos.z + 0.30f };

			double distance = sqrt(pow(cp_pos.x - my_pos.x, 2) + pow(cp_pos.y - my_pos.y, 2) + pow(cp_pos.z - my_pos.z, 2));

			double distance_c_1 = sqrt(pow(crnr_1.x - my_pos.x, 2) + pow(crnr_1.y - my_pos.y, 2) + pow(crnr_1.z - my_pos.z, 2));
			double distance_c_2 = sqrt(pow(crnr_2.x - my_pos.x, 2) + pow(crnr_2.y - my_pos.y, 2) + pow(crnr_2.z - my_pos.z, 2));
			double distance_c_3 = sqrt(pow(crnr_3.x - my_pos.x, 2) + pow(crnr_3.y - my_pos.y, 2) + pow(crnr_3.z - my_pos.z, 2));
			double distance_c_4 = sqrt(pow(crnr_4.x - my_pos.x, 2) + pow(crnr_4.y - my_pos.y, 2) + pow(crnr_4.z - my_pos.z, 2));
			
			std::vector<double> closest_crn;
			closest_crn.push_back(distance_c_1);
			closest_crn.push_back(distance_c_2);
			closest_crn.push_back(distance_c_3);
			closest_crn.push_back(distance_c_4), axis::_vec_sort(closest_crn);
			
			vec3 closest_crnr_1, closest_crnr_2;
			
			for (size_t x = 0; x < 2; ++x) {

				if (closest_crn[x] == distance_c_1) if (x == 0) closest_crnr_1 = crnr_1; else if (x == 1) closest_crnr_2 = crnr_1;
				if (closest_crn[x] == distance_c_2) if (x == 0) closest_crnr_1 = crnr_2; else if (x == 1) closest_crnr_2 = crnr_2;
				if (closest_crn[x] == distance_c_3) if (x == 0) closest_crnr_1 = crnr_3; else if (x == 1) closest_crnr_2 = crnr_3;
				if (closest_crn[x] == distance_c_4) if (x == 0) closest_crnr_1 = crnr_4; else if (x == 1) closest_crnr_2 = crnr_4;

			}

			vec3 closest_point = closest_crnr_1;

			if (closest_crnr_1.x == closest_crnr_2.x) { closest_point.z = my_pos.z; 

				if (!axis::_in_range(closest_point.z, closest_crnr_1.z, closest_crnr_2.z)) closest_point = closest_crnr_1;

			}

			else 

			if (closest_crnr_2.z == closest_crnr_2.z) { closest_point.x = my_pos.x;

				if (!axis::_in_range(closest_point.x, closest_crnr_1.x, closest_crnr_2.x)) closest_point = closest_crnr_1;

			}

			double distance_x = closest_point.x - my_pos.x, distance_z = closest_point.z - my_pos.z;

			float dif = (float)atan2((float)distance_z, (float)distance_x) * 180.f / M_PI - 90.f;

			dif = fmodf(dif - my_yaw, 360.f);
			if (dif >= 180.0f) dif -= 360.0f;
			if (dif < -180.0f) dif += 360.0f; if (abs(dif) <= 0.1) continue;

			float tmp = axis::mc_msense * 0.600f + 0.200f, actual_mc_sense = pow(tmp, 3) * 8.00f;
			
			if (abs(dif) < 2.0f) dif = axis::_rand_val(1.f, 2.f) * (abs(dif) / dif);
			dif *= actual_mc_sense * (aim_speed + (int)axis::_rand_val(1.0f, 4.0f));

			float new_yaw_a = my_yaw + (int)dif * 0.0015f, prv_yaw_a = my_pyaw + (int)dif * 0.0015f;
			axis::local_player->set_yaw(new_yaw_a), axis::local_player->set_previous_yaw(prv_yaw_a);

		}

	}

}