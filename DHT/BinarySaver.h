#pragma once

#include "Types.h"
#include "Worker.h"

#include <string>

class BinarySaver : public Worker<std::string, byte_seq> {
public:
	// param(id) - asset id
	// param(data_to_process) - binary image representation to be saved
	// return - the saved image
	virtual byte_seq Process(const std::string& id, const byte_seq& data_to_process) override;
};