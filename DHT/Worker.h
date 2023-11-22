#pragma once

template<class InitialData, class ProcessedData>
class Worker {
public:
	virtual ProcessedData Process(const InitialData& data, const ProcessedData& data_to_process) = 0;
};