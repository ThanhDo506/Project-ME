#ifndef EVENT_H
#define EVENT_H

#include <functional>

enum EventType {
	None = 0,
	AwakeEvent,
	StartEvent,
	TriggeredEvent,
	CollisionEvent,
	EnableEvent,
	DisableEvent,
	DestroyEvent,
	UpdateRenderingEvent,
};

class IEvent
{
public:
	using EventHandler = std::function<void()>;

	virtual EventType getEventType() const = 0;

	virtual void perform(const EventHandler& eventHandler) = 0;

	virtual bool operator<(const IEvent& const e);
};

#endif // !EVENT_H
