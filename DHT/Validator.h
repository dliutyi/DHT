#pragma once

#include "Types.h"
#include "Worker.h"

#include <string>

class Validator : public Worker<std::string, byte_seq> {
public:
	virtual byte_seq Process(const std::string& id, const byte_seq& data_to_process) override;
};
