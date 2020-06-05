#include "Event.h"

Event::Event(int seqId, std::string eventId, std::list<int> items)
	: seqId(seqId), eventId(eventId), items(items) {}
