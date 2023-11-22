#pragma once

#include <png.h>

#include "Types.h"

class PNGImage {
public:
	PNGImage();
	PNGImage(const PNGImage&) = delete;
	PNGImage& operator=(const PNGImage&) = delete;
	~PNGImage();

	void Initialize(int width, int height, int bit_depth);
	void Encode();
	void AddPayload(const byte_seq& payload);

	const byte_seq& GetImage() const {
		return image;
	}

private:
	static void WriterCallback(png_structp png_ptr, png_bytep data, png_size_t length);

private:
	png_structp png_ptr;
	png_infop info_ptr;
	byte_seq payload;
	byte_seq image;
	unsigned char* week_payload_addr;
};