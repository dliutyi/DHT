#pragma once

#include <string>

struct Configuration {
	std::string input_file = "test.txt";
	std::string output_folder = "output";
	std::string image_format = ".png";
	int width = 256;
	int height = 1;
	int bit_depth = 1;
};

extern Configuration Config;