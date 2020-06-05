#pragma once

#include <list>
#include <string>


class Event {
private:
	int seqId;
	std::string eventId;
	std::list<int> items;
public:
	Event(int seqId, std::string eventId, std::list<int> items);
};