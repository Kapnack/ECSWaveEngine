#pragma once

#include <vector>
#include "Subscriber.h"
#include "Export.h"

using namespace std;

template<typename TReturnType, typename... TParameters>
class WAVEEXPORT Func
{
private:

	Subscriber subscriber;

public:

	template<typename TObject>
	void Subscribe(TObject* instance, TReturnType(TObject::* method)(TParameters...))
	{
		subscriber.instance = instance;
		subscriber.method = *(void**)&method;

		subscriber.invoke =
			[](void* obj, void* m, const void*)
			{
				TObject* o = static_cast<TObject*>(obj);

				TReturnType(TObject:: * methodPtr)() = *(TReturnType(TObject::**)(TParameters...)) & m;

				return (o->*methodPtr)();
			};
	}

	template<typename TObject>
	void Subscribe(TObject* instance, TReturnType(TObject::* method)())
	{
		subscriber.instance = instance;
		subscriber.method = *(void**)&method;

		subscriber.invoke =
			[](void* obj, void* m, const void*)
			{
				TObject* o = static_cast<TObject*>(obj);

				TReturnType(TObject:: * methodPtr)() = *(TReturnType(TObject::**)()) & m;

				return (o->*methodPtr)();
			};
	}

	void Subscribe(TReturnType(*func)(TParameters...))
	{
		subscriber.instance = nullptr;
		subscriber.method = reinterpret_cast<void*>(func);

		subscriber.invoke =
			[](void*, void* m, const void* event)
			{
				TReturnType(*funcPtr)(TParameters...) = reinterpret_cast<TReturnType(*)(TParameters...)>(m);

				const TParameters* e = static_cast<const TParameters*>(event);

				return funcPtr(*e);
			};
	}

	void Subscribe(TReturnType(*func)())
	{
		subscriber.instance = nullptr;
		subscriber.method = reinterpret_cast<void*>(func);

		subscriber.invoke =
			[](void*, void* m, const void*)
			{
				TReturnType(*funcPtr)() = reinterpret_cast<TReturnType(*)()>(m);

				return funcPtr();
			};
	}

	void Unsubscribe()
	{
		subscriber.instance = nullptr;
		subscriber.method = nullptr;
		subscriber.invoke = nullptr;
	}

	TReturnType Invoke(TParameters... args) const
	{
		return subscriber.invoke(args...);
	}
};