#include "PNGImage.h"

PNGImage::PNGImage()
	: png_ptr(nullptr)
	, info_ptr(nullptr)
	, payload()
	, image()
	, week_payload_addr(nullptr) { }

void PNGImage::Initialize(int width, int height, int bit_depth) {
	this->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (!this->png_ptr) {
		throw std::exception("The problem occuried while creating of PNG struct");
	}

	this->info_ptr = png_create_info_struct(this->png_ptr);
	if (!this->info_ptr) {
		throw std::exception("The problem occuried while creating of PNG info struct");
	}

	if (setjmp(png_jmpbuf(this->png_ptr))) {
		throw std::exception("The problem occuried while buffer intialization");
	}

	png_set_IHDR(this->png_ptr, this->info_ptr, width, height, bit_depth,
		PNG_COLOR_TYPE_GRAY,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT);
}

void PNGImage::Encode() {
	if (!this->week_payload_addr) {
		throw std::exception("The payload has not been added");
	}

	png_set_write_fn(this->png_ptr, &this->image, (png_rw_ptr)&PNGImage::WriterCallback, nullptr);
	png_write_png(this->png_ptr, this->info_ptr, PNG_TRANSFORM_IDENTITY, nullptr);
}

void PNGImage::AddPayload(const byte_seq& payload) {
	this->payload = payload;
	this->week_payload_addr = this->payload.data(); // save pointer to the payload data for usage outside the function scope
	png_set_rows(this->png_ptr, this->info_ptr, (png_bytepp)&this->week_payload_addr);
}

PNGImage::~PNGImage() {
	if (this->info_ptr != nullptr) {
		png_free_data(this->png_ptr, this->info_ptr, PNG_FREE_ALL, -1);
	}

	if (this->png_ptr != nullptr) {
		png_destroy_write_struct(&this->png_ptr, (png_infopp)nullptr);
	}

	this->info_ptr = nullptr;
	this->png_ptr = nullptr;
}

void PNGImage::WriterCallback(png_structp png_ptr, png_bytep data, png_size_t length) {
	byte_seq* ps = (byte_seq*)png_get_io_ptr(png_ptr);
	ps->insert(ps->end(), data, data + length);
}