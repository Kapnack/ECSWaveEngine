#pragma once

#include "Delegate.h"

#include <vector>

#include "Subscriber.h"

using namespace std;

template<typename... TParams>
class Action : public Delegate
{
private:

	vector<Subscriber<void, TParams...>> subscribers;

public:

	template<typename TObject>
	void Subscribe(TObject* instance, void(TObject::* method)(TParams...))
	{
		Subscriber<void, TParams...> sub;

		sub.instance = instance;
		sub.method = *reinterpret_cast<void**>(&method);
		   
		sub.invoke =
			[](void* obj, void* m, TParams... params)
			{
				TObject* o = static_cast<TObject*>(obj);

				void(TObject:: * methodPtr)(TParams...) = *(void(TObject::**)(TParams...)) & m;

				(o->*methodPtr)(params...);
			};

		subscribers.push_back(sub);
	}

	template<typename TObject>
	void SubscribeNoArgs(TObject* instance, void(TObject::* method)())
	{
		Subscriber<void> sub;
	
		sub.instance = instance;
		sub.method = *reinterpret_cast<void**>(&method);
	
		sub.invoke =
			[](void* obj, void* m, TParams...)
			{
				TObject* o = static_cast<TObject*>(obj);
	
				void(TObject:: * methodPtr)() = *(void(TObject::**)()) & m;
	
				(o->*methodPtr)();
			};
	
		subscribers.push_back(sub);
	}

	void Subscribe(void(*func)(TParams...))
	{
		Subscriber<void, TParams...> sub;
	
		sub.instance = nullptr;
		sub.method = reinterpret_cast<void*>(func);
	
		sub.invoke =
			[](void*, void* m, TParams... parms)
			{
				void(*funcPtr)(TParams...) = static_cast<void(*)(TParams...)>(m);
	
				funcPtr(parms...);
			};
	
		subscribers.push_back(sub);
	}

	void SubscribeNoArgs(void(*func)())
	{
		Subscriber<void, TParams...> sub;
	
		sub.instance = nullptr;
		sub.method = reinterpret_cast<void*>(func);
	
		sub.invoke =
			[](void*, void* m, TParams...)
			{
				void(*funcPtr)() = reinterpret_cast<void(*)()>(m);
	
				funcPtr();
			};
	
		subscribers.push_back(sub);
	}

	void UnsubscribeNoArgs(void(*func)())
	{
		void* m = *reinterpret_cast<void**>(&func);
	
		subscribers.erase(
			remove_if(subscribers.begin(), subscribers.end(),
				[&](const Subscriber<void, TParams...>& s)
				{
					return s.instance == nullptr && s.method == m;
				}),
			subscribers.end()
		);
	}

	void Unsubscribe(void(*func)(TParams...))
	{
		void* m = *reinterpret_cast<void**>(&func);
	
		subscribers.erase(
			remove_if(subscribers.begin(), subscribers.end(),
				[&](const Subscriber<void, TParams...>& s)
				{
					return s.instance == nullptr && s.method == m;
				}),
			subscribers.end()
		);
	}

	template<typename TObject>
	void Unsubscribe(TObject* instance, void(TObject::* method)(TParams...))
	{
		void* m = *reinterpret_cast<void**>(&method);

		subscribers.erase(
			remove_if(subscribers.begin(), subscribers.end(),
				[&](const Subscriber<void, TParams...>& s)
				{
					return s.instance == instance && s.method == m;
				}),
			subscribers.end()
		);
	}

	template<typename TObject>
	void UnsubscribeNoArgs(TObject* instance, void(TObject::* method)())
	{
		void* m = *reinterpret_cast<void**>(&method);
	
		subscribers.erase(
			remove_if(subscribers.begin(), subscribers.end(),
				[&](const Subscriber<void, TParams...>& s)
				{
					return s.instance == instance && s.method == m;
				}),
			subscribers.end()
		);
	}

	void Invoke(TParams... args) const
	{
		for (const Subscriber<void, TParams...>& sub : subscribers)
			sub.invoke(sub.instance, sub.method, args...);
	}
};