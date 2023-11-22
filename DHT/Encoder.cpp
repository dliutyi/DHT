#include "Encoder.h"
#include "Configuration.h"

#include <string>

byte_seq Encoder::Process(const std::string& id, const byte_seq& data_to_process) {
	debug("Process processing - %s\n", id.c_str());

	const unsigned char display_digit[] = {
		0b01110111, // 0
		0b01000010,	// 1
		0b10110110,	// 2
		0b11010110,	// 3
		0b11000011,	// 4
		0b11010101,	// 5
		0b11110101,	// 6
		0b01000110,	// 7
		0b11110111,	// 8
		0b11010111	// 9
	};

	unsigned char ones = 0b11111111;
	byte_seq processed(Config.width / 8, ones);

	const auto& checksum = this->calculateChecksum(data_to_process);
	int index = 1;

	for (size_t i = 0; i < checksum.size(); ++i) {
		processed[index++] = ~display_digit[checksum[i]];
	}

	for (size_t i = 0; i < id.size(); ++i) {
		processed[index++] = ~display_digit[data_to_process[i]];
	}

	return processed;
}

byte_seq Encoder::calculateChecksum(const byte_seq& id) {
	int sum = 0;
	int multiplier = 1;
	for (auto c : id) {
		sum += multiplier * c;
		multiplier *= 10;
	}

	int checksum = sum % 97;
	if (checksum < 10) {
		return { 0, static_cast<unsigned char>(checksum) };
	}
	else {
		return { static_cast<unsigned char>(checksum / 10), static_cast<unsigned char>(checksum % 10) };
	}
}