#pragma once

namespace GE
{

	class IObservable;

	class IObserver
	{
		public:
			virtual ~IObserver() = default;

			virtual void updateEvent(const IObservable * observable) = 0;
	};

} // GE
