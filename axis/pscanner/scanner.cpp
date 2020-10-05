
#include "scanner.h"

size_t scanner::pattern(size_t min, size_t max, std::vector<int> pattern) {

	size_t pattern_size = pattern.size();

	for (size_t address = min; address < max; address += 100000) {

		std::vector<byte>memory(100000);
		if (!NT_SUCCESS(ZwReadVirtualMemory(axis::p_handle, (LPVOID)address, &memory[0], 100000, 0)))
			continue;

		for (size_t it = 0; it < 100000; ++it) {

			if (address + it >= max) break;

			bool should_check = true;

			if (pattern[0] != RAND) {

				if (memory[it] != pattern[0])
					should_check = false;

			}

			if (should_check) {

				bool is_pattern = true;

				for (size_t x = 0; x < pattern.size(); ++x) {

					if (pattern[x] == RAND) continue;

					if (pattern[x] != memory[it + x]) {

						is_pattern = false;
						break;

					}

				}

				if (is_pattern) return address + it;

			}

		}

	}

	return 0;

}