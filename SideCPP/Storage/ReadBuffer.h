#pragma once
#include <algorithm>
#include "BufferBase.h"


class ReadBuffer: public BufferBase {

public:

	ReadBuffer(Position begin_pos_, Position end_pos_): BufferBase(begin_pos_, end_pos_) {}

	size_t read(char* to, size_t n) {
		
		size_t bytes_copied = 0;

		while (bytes_copied < n) {
			size_t bytes_to_copie = std::min(static_cast<size_t>(working_buffer.end() - pos), n - bytes_copied);
			bytes += bytes_to_copie;
			bytes_copied += bytes_to_copie;
		}

		return bytes_copied;
	}
};