#pragma once

#include "Types.h"
#include "Worker.h"

#include <string>

class Encoder : public Worker<std::string, byte_seq> {
public:
	// param(id) - asset id
	// param(data_to_process) - vector of digits of asset id
	// return - vector of checksum and digits encoded based seven segment display in 1..6 bytes, enriched with 0, 7..32 reserved bytes
	virtual byte_seq Process(const std::string& id, const byte_seq& data_to_process) override;

private:
	byte_seq calculateChecksum(const byte_seq& id);
};
