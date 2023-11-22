#include "Validator.h"
#include "Types.h"

#include <string>

byte_seq Validator::Process(const std::string& id, const byte_seq& data_to_process) {
	debug("Validor processing - %s\n", id.c_str());

	if (id.size() != 4) {
		throw std::exception("Invalid number of digits");
	}

	byte_seq processed;
	processed.resize(4, 0);

	for (size_t i = 0; i < id.size(); ++i) {
		if (id[i] < '0' || id[i] > '9') {
			throw std::exception("The ID should be consisted of digits");
		}
		processed[i] = id[i] - '0';
	}

	return processed;
}