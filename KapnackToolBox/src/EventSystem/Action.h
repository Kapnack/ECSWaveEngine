#pragma once

#include "Delegate.h"

#include <vector>
#include "Subscriber.h"
#include <utility>

using namespace std;

template<typename... TParameters>
class Action : public Delegate
{
private:

	vector<Subscriber<void>> subscribers;

	using ArgsTuple = tuple<TParameters...>;

public:

	template<typename TObject>
	void Subscribe(TObject* instance, void(TObject::* method)(TParameters...))
	{
		Subscriber<void> sub;

		sub.instance = instance;
		sub.method = *(void**)&method;

		sub.invoke =
			[](void* obj, void* m, const void* event)
			{
				TObject* o = static_cast<TObject*>(obj);

				void(TObject:: * methodPtr)(TParameters...) = *(void(TObject::**)(TParameters...)) & m;

				const ArgsTuple* argsTuple = static_cast<const ArgsTuple*>(event);

				apply(
					[o, methodPtr](TParameters... params)
					{
						(o->*methodPtr)(params...);
					},
					*argsTuple
				);
			};

		subscribers.push_back(sub);
	}

	template<typename TObject>
	void SubscribeNoArgs(TObject* instance, void(TObject::* method)())
	{
		Subscriber<void> sub;

		sub.instance = instance;
		sub.method = *(void**)&method;

		sub.invoke =
			[](void* obj, void* m, const void*)
			{
				TObject* o = static_cast<TObject*>(obj);

				void(TObject:: * methodPtr)() = *(void(TObject::**)()) & m;

				(o->*methodPtr)();
			};

		subscribers.push_back(sub);
	}

	void Subscribe(void(*func)(TParameters...))
	{
		Subscriber<void> sub;

		sub.instance = nullptr;
		sub.method = reinterpret_cast<void*>(func);

		sub.invoke =
			[](void*, void* m, const void* event)
			{
				void(*funcPtr)(TParameters...) = reinterpret_cast<void(*)(TParameters...)>(m);

				const ArgsTuple* argsTuple = static_cast<const ArgsTuple*>(event);

				apply(funcPtr, *argsTuple);
			};

		subscribers.push_back(sub);
	}

	void SubscribeNoArgs(void(*func)())
	{
		Subscriber<void> sub;

		sub.instance = nullptr;
		sub.method = reinterpret_cast<void*>(func);

		sub.invoke =
			[](void*, void* m, const void*)
			{
				void(*funcPtr)() = reinterpret_cast<void(*)()>(m);

				funcPtr();
			};

		subscribers.push_back(sub);
	}

	void UnsubscribeNoArgs(void(*func)())
	{
		void* m = *(void**)&func;

		subscribers.erase(
			remove_if(subscribers.begin(), subscribers.end(),
				[&](const Subscriber<void>& s)
				{
					return s.instance == nullptr && s.method == m;
				}),
			subscribers.end()
		);
	}

	void Unsubscribe(void(*func)(TParameters...))
	{
		void* m = *(void**)&func;

		subscribers.erase(
			remove_if(subscribers.begin(), subscribers.end(),
				[&](const Subscriber<void>& s)
				{
					return s.instance == nullptr && s.method == m;
				}),
			subscribers.end()
		);
	}

	template<typename TObject>
	void Unsubscribe(TObject* instance, void(TObject::* method)(TParameters...))
	{
		void* m = *(void**)&method;

		subscribers.erase(
			remove_if(subscribers.begin(), subscribers.end(),
				[&](const Subscriber<void>& s)
				{
					return s.instance == instance && s.method == m;
				}),
			subscribers.end()
		);
	}

	template<typename TObject>
	void UnsubscribeNoArgs(TObject* instance, void(TObject::* method)())
	{
		void* m = *(void**)&method;

		subscribers.erase(
			remove_if(subscribers.begin(), subscribers.end(),
				[&](const Subscriber<void>& s)
				{
					return s.instance == instance && s.method == m;
				}),
			subscribers.end()
		);
	}

	void Invoke(TParameters... args) const
	{
		ArgsTuple packedArgs(args...);

		for (const Subscriber<void>& sub : subscribers)
			sub.invoke(sub.instance, sub.method, static_cast<const void*>(&packedArgs));
	}
};