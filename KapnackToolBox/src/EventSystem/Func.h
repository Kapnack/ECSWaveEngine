#pragma once


#include "Delegate.h"

#include "Subscriber.h"
#include "Export.h"

using namespace std;


template<typename TReturn, typename... TParams>
class Func : public Delegate
{
private:

	Subscriber<TReturn, TParams...> subscriber;

public:

	template<typename TObject>
	void Subscribe(TObject* instance, TReturn(TObject::* method)(TParams...))
	{
		subscriber.instance = instance;
		subscriber.method = *(void**)&method;

		subscriber.invoke =
			[](void* obj, void* m, TParams... params) -> TReturn
			{
				TObject* o = static_cast<TObject*>(obj);

				TReturn(TObject:: * methodPtr)(TParams...) = *(TReturn(TObject::**)(TParams...)) & m;

				return (o->*methodPtr)(params...);
			};
	}

	template<typename TObject>
	void SubscribeNoArgs(TObject* instance, TReturn(TObject::* method)())
	{
		subscriber.instance = instance;
		subscriber.method = *(void**)&method;

		subscriber.invoke =
			[](void* obj, void* m, TParams...)
			{
				TObject* o = static_cast<TObject*>(obj);

				TReturn(TObject:: * methodPtr)() = *(TReturn(TObject::**)()) & m;

				return (o->*methodPtr)();
			};
	}

	void Subscribe(TReturn(*func)(TParams...))
	{
		subscriber.instance = nullptr;
		subscriber.method = reinterpret_cast<void*>(func);

		subscriber.invoke =
			[](void*, void* m, TParams... params) -> TReturn
			{
				TReturn(*funcPtr)(TParams...) = reinterpret_cast<TReturn(*)(TParams...)> (m);

				return funcPtr(params...);
			};
	}

	void SubscribeNoArgs(TReturn(*func)())
	{
		subscriber.instance = nullptr;
		subscriber.method = reinterpret_cast<void*>(func);

		subscriber.invoke =
			[](void*, void* m, TParams...)
			{
				TReturn(*funcPtr)() = reinterpret_cast<TReturn(*)()>(m);

				return funcPtr();
			};
	}

	void Unsubscribe()
	{
		subscriber.instance = nullptr;
		subscriber.method = nullptr;
		subscriber.invoke = nullptr;
	}

	TReturn Invoke(TParams... args) const
	{
		return subscriber.invoke(subscriber.instance, subscriber.method, args...);
	}
};