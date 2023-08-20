#pragma once
#include <stdio.h>


class BufferBase {

public:

	using Position = char*;

	
	struct Buffer {

		Buffer(Position begin_pos_, Position end_pos_) : begin_pos(begin_pos_), end_pos(end_pos_) {}

		inline Position begin() { return begin_pos; };
		inline Position end() { return end_pos; };
		Position begin_pos;
		Position end_pos;
	};

protected:

	Position pos;
};