#include "PNGEncoder.h"
#include "PNGImage.h"
#include "Configuration.h"

byte_seq PNGEncoder::Process(const std::string& id, const byte_seq& data_to_process) {
	debug("PNGEncoder processing - %s\n", id.c_str());

	PNGImage png;
	png.Initialize(Config.width, Config.height, Config.bit_depth);
	png.AddPayload(data_to_process);
	png.Encode();

	return png.GetImage();
}