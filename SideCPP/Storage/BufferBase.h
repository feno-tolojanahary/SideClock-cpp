#pragma once
#include <stdio.h>


class BufferBase {

public:

	using Position = char*;
	
	struct Buffer {

		Buffer(Position begin_pos_, Position end_pos_) : begin_pos(begin_pos_), end_pos(end_pos_) {}

		inline Position begin() { return begin_pos; };
		inline Position end() { return end_pos; };
		
	private:
		
		Position begin_pos;
		Position end_pos;
	};

	BufferBase(Position ptr, size_t size, size_t offset)
		: pos(ptr + offset), working_buffer(ptr, ptr + size), internal_buffer(ptr, ptr + size) {}

protected:

	size_t bytes = 0;

	/// A reference to a piece of memory for the buffer.
	Buffer internal_buffer;

	Position pos;
	Buffer working_buffer;
};