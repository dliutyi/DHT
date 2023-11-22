#include "Controller.h"
#include "Configuration.h"

#include "Validator.h"
#include "Encoder.h"
#include "PNGEncoder.h"
#include "BinarySaver.h"

#include <fstream>
#include <vector>

Controller::Controller()
	: is_read_completed(false)
{ }

void Controller::Start(const std::string& file_path) {
	this->InitializePipeline();

	this->is_read_completed = false;
	this->process_loop = std::async(&Controller::Loop, this);
	this->reading_loop = std::async(&Controller::ReadIDs, this, file_path);

	this->reading_loop.get();
	this->process_loop.get();
}

void Controller::InitializePipeline() {
	pipeline.AddExceptionHandler([](std::exception& ex, const std::string& id, const byte_seq& processed_data) {
		debug("\tException(%s) occuried in %s\n", ex.what(), id.c_str());
	});

	pipeline.Add<Validator>();
	pipeline.Add<Encoder>();
	pipeline.Add<PNGEncoder>();
	pipeline.Add<BinarySaver>();
}

void Controller::Loop() {
	std::vector<std::future<byte_seq>> workers;
	while (!this->is_read_completed || !this->lines.empty()) {
		volatile bool isEmpty = this->lines.empty();
		if (isEmpty) {
			std::unique_lock<std::mutex> lk(mut);
			cond_var.wait(lk);
		}

		auto line = this->lines.front();
		this->lines.pop();

		auto fut = std::async(&PipelineProcessor<std::string, byte_seq>::Process, &this->pipeline, line, byte_seq { });
		workers.emplace_back(std::move(fut));
	}

	for (auto& w : workers) {
		w.get();
	}
}

void Controller::ReadIDs(const std::string& file_path) {
	std::ifstream file(file_path);
	while (!file.eof()) {
		std::string line;
		file >> line;

		this->lines.push(line);
		cond_var.notify_one();
	}

	this->is_read_completed = true;
}