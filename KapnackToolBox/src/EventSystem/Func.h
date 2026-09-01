#pragma once

#include "Delegate.h"

#include <tuple>
#include <utility>

#include "Subscriber.h"

using namespace std;

template<typename TReturnType, typename... TParameters>
class Func : Delegate
{
private:

	Subscriber<TReturnType> subscriber;

	using ArgsTuple = tuple<TParameters...>;

public:

	template<typename TObject>
	void Subscribe(TObject* instance, TReturnType(TObject::* method)(TParameters...))
	{
		subscriber.instance = instance;
		subscriber.method = *(void**)&method;

		subscriber.invoke =
			[](void* obj, void* m, const void* event) -> TReturnType
			{
				TObject* o = static_cast<TObject*>(obj);

				TReturnType(TObject:: * methodPtr)(TParameters...) = *(TReturnType(TObject::**)(TParameters...)) & m;

				const ArgsTuple* argsTuple = static_cast<const ArgsTuple*>(event);

				return apply(
					[o, methodPtr](TParameters... params) -> TReturnType
					{
						return (o->*methodPtr)(params...);
					},
					*argsTuple
				);
			};
	}

	template<typename TObject>
	void SubscribeNoArgs(TObject* instance, TReturnType(TObject::* method)())
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
			[](void*, void* m, const void* event) -> TReturnType
			{
				TReturnType(*funcPtr)(TParameters...) = reinterpret_cast<TReturnType(*)(TParameters...)> (m);

				const ArgsTuple* argsTuple = static_cast<const ArgsTuple*>(event);

				return apply(funcPtr, *argsTuple);
			};
	}

	void SubscribeNoArgs(TReturnType(*func)())
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
		ArgsTuple packedArgs(args...);

		return subscriber.invoke(subscriber.instance, subscriber.method, static_cast<const void*>(&packedArgs));
	}
};