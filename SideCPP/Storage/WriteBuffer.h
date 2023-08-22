#pragma once
#include "BufferBase.h"

class WriteBuffer : public BufferBase {

public:

	WriteBuffer(Position begin_pos_, Position end_pos_) : BufferBase(begin_pos_, end_pos_) {}


};