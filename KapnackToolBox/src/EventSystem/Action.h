#pragma once

#include <vector>
#include "Subscriber.h"
#include "Export.h"

using namespace std;

class Delegate
{

};

template<typename... TParameters>
class WAVEEXPORT Action : public Delegate
{
private:

    vector<Subscriber> subscribers;

public:

    template<typename TObject>
    void Subscribe(TObject* instance, void(TObject::* method)(TParameters...))
    {
		Subscriber sub;

		sub.instance = instance;
		sub.method = *(void**)&method;

		sub.invoke =
			[](void* obj, void* m, const void*)
			{
				TObject* o = static_cast<TObject*>(obj);

				void(TObject:: * methodPtr)() = *(void(TObject::**)(TParameters...)) & m;

				(o->*methodPtr)();
			};

		subscribers.push_back(sub);
    }

	template<typename TObject>
	void Subscribe(TObject* instance, void(TObject::* method)())
	{
		Subscriber sub;

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
		Subscriber sub;

		sub.instance = nullptr;
		sub.method = reinterpret_cast<void*>(func);

		sub.invoke =
			[](void*, void* m, const void* event)
			{
				void(*funcPtr)(TParameters...) = reinterpret_cast<void(*)(TParameters...)>(m);

				const TParameters* e = static_cast<const TParameters*>(event);

				funcPtr(*e);
			};

		subscribers.push_back(sub);
	}

	void Subscribe(void(*func)())
	{
		Subscriber sub;

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

	void Unsubscribe(void(*func)())
	{
		void* m = *(void**)&func;

		subscribers.erase(
			remove_if(subscribers.begin(), subscribers.end(),
				[&](const Subscriber& s)
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
				[&](const Subscriber& s)
				{
					return s.instance == instance && s.method == m;
				}),
			subscribers.end()
		);
	}

	template<typename TObject>
	void Unsubscribe(TObject* instance, void(TObject::* method)())
	{
		void* m = *(void**)&method;

		subscribers.erase(
			remove_if(subscribers.begin(), subscribers.end(),
				[&](const Subscriber& s)
				{
					return s.instance == instance && s.method == m;
				}),
			subscribers.end()
		);
	}

    void Invoke(TParameters... args) const
    {
        for (const Subscriber& sub : subscribers)
            sub.invoke(args...);
    }
};