#pragma once

#include "ServiceProvider/Service.h"

#include <queue>
#include <typeindex>
#include <unordered_map>

#include "Event.h"
#include "Action.h"
#include "Delegate.h"

using namespace std;

namespace WaveEngine
{
	template<typename TEvent>
	concept AvailableEvent = derived_from<TEvent, Event>;

	class EventSystem : public Service
	{
	private:

		unordered_map<type_index, Delegate*> subscribers;
		unordered_map<type_index, queue<Event*>> events;

	public:

		inline EventSystem() : Service()
		{
		}

		inline ~EventSystem()
		{
			for (unordered_map<type_index, queue<Event*>>::iterator it = events.begin(); it != events.end(); ++it)
			{
				while (!it->second.empty())
				{
					delete it->second.front();
					it->second.pop();
				}
			}

			for (unordered_map<type_index, Delegate*>::iterator it = subscribers.begin(); it != subscribers.end(); ++it)
				delete it->second;
		}

		template<AvailableEvent TEvent>
		void Subscribe(void(*func)(const TEvent&))
		{
			type_index eventType = typeid(TEvent);

			events[eventType];

			if (!subscribers.contains(eventType))
				subscribers[eventType] = new Action<const TEvent&>();

			static_cast<Action<const TEvent&>*>(subscribers[eventType])->Subscribe(func);
		}

		template<AvailableEvent TEvent, typename TObject>
		void Subscribe(TObject* instance, void(TObject::* method)(const TEvent&))
		{
			type_index eventType = typeid(TEvent);

			events[eventType];

			if (!subscribers.contains(eventType))
				subscribers[eventType] = new Action<const TEvent&>();

			static_cast<Action<const TEvent&>*>(subscribers[eventType])->Subscribe(instance, method);
		}

		template<AvailableEvent TEvent>
		void Unsubscribe(void(*func)(const TEvent&))
		{
			type_index eventType = typeid(TEvent);

			if (!subscribers.contains(eventType))
				return;

			static_cast<Action<const TEvent&>*>(subscribers[eventType])->Unsubscribe(func);
		}

		template<AvailableEvent TEvent, typename TObject>
		void Unsubscribe(TObject* instance, void(TObject::* method)(const TEvent&))
		{
			type_index eventType = typeid(TEvent);

			if (!subscribers.contains(eventType))
				return;

			static_cast<Action<const TEvent&>*>(subscribers[eventType])->Unsubscribe(instance, method);
		}

		template<AvailableEvent TEvent, typename... T>
		void Invoke(T... data)
		{
			type_index eventType = typeid(TEvent);

			if (!subscribers.contains(eventType))
				return;

			queue<Event*>& queue = events[eventType];

			TEvent* event;

			if (!queue.empty())
			{
				event = static_cast<TEvent*>(queue.front());
				queue.pop();
			}
			else
			{
				event = new TEvent();
			}

			*event = TEvent{ data... };

			static_cast<Action<const TEvent&>*>(subscribers[eventType])->Invoke(*event);

			event->Reset();

			queue.push(event);
		}
	};
}