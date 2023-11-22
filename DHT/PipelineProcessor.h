#pragma once

#include "Types.h"
#include "Worker.h"

#include <vector>
#include <memory>
#include <functional>

template<class InitialData, class ProcessedData>
class PipelineProcessor : Worker<InitialData, ProcessedData> {
public:
	template<class T> 
	void Add() {
		this->workers.emplace_back(std::make_unique<T>());
	}

	void AddExceptionHandler(std::function<void(std::exception& ex, const InitialData& data, const ProcessedData& data_to_process)> func) {
		this->exception_handler = func;
	}

	virtual ProcessedData Process(const InitialData& data, const ProcessedData& data_to_process) override {
		InitialData initial_data(data);
		ProcessedData processed(data_to_process);
		for (auto& worker : this->workers) {
			try {
				processed = worker->Process(initial_data, processed);
			}
			catch (std::exception& ex) {
				this->exception_handler(ex, initial_data, processed);
				break;
			}

		}
		return processed;
	}

private:
	std::function<void(std::exception& ex, const InitialData& data, const ProcessedData& data_to_process)> exception_handler;
	std::vector<std::unique_ptr<Worker<InitialData, ProcessedData>>> workers;
};
