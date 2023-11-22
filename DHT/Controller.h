#pragma once

#include "Types.h"
#include "PipelineProcessor.h"

#include <string>
#include <future>
#include <queue>
#include <mutex>

class Controller {
public:
	Controller();
	void Start(const std::string& file_path);

private:
	void InitializePipeline();
	void Loop();
	void ReadIDs(const std::string& file_path);

private:
	volatile bool is_read_completed;

	std::future<void> process_loop;
	std::future<void> reading_loop;

	std::queue<std::string> lines;

	std::mutex mut;
	std::condition_variable cond_var;

	PipelineProcessor<std::string, byte_seq> pipeline;
};