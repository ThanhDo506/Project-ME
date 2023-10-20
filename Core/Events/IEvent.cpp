#include "IEvent.h"

bool IEvent::operator<(const IEvent& const e)
{
	return this->getEventType() < e.getEventType();
}
