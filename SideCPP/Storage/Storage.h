#pragma once


template <typename Model>
class Storage {

	Storage(char* filename_): filename(filename_) {}

private:

	char* filename;
};