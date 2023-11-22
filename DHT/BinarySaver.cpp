#include "BinarySaver.h"
#include "Configuration.h"

#include <fstream>
#include <string>

byte_seq BinarySaver::Process(const std::string& id, const byte_seq& data_to_process) {
	debug("BinarySaver processing - %s\n", id.c_str());

	std::string file_name = Config.output_folder + "/" + id + Config.image_format;
	std::ofstream file(file_name, std::ios::binary);
	file.write((char*)data_to_process.data(), data_to_process.size());
	file.close();

	return data_to_process;
}