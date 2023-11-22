#pragma once

#include <string>

#include "Types.h"
#include "Worker.h"

class PNGEncoder : public Worker<std::string, byte_seq> {
public:
	// param(id) - asset id
	// param(data_to_process) - payload to visualize in PNG
	// return - binary PNG representation  
	virtual byte_seq Process(const std::string& id, const byte_seq& data_to_process) override;
};