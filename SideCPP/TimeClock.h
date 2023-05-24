#include <ctime>

class TimeClock
{

private:
	int id;
	int owner;
	time_t startDate;
	time_t endDate;

public:

	TimeClock();
	~TimeClock();
};