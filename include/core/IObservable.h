#pragma once

#include <deque>
#include <algorithm>

#include "core/IObserver.h"

namespace GE
{

	class IObserver;

	class IObservable
	{
		public:
			// Actions
			bool addObserver(IObserver * observer);
			bool removeObserver(IObserver * observer);
			void notifyObservers() const;
			[[nodiscard]] bool hasObservers() const;

			// Getters
			[[nodiscard]] size_t getObserversCount() const;

		protected:
			// Move constructor/destructor to protected part for preventing class instantion.
			IObservable() = default;
			virtual ~IObservable() = default;

		private:
			size_t m_observersCount { 0 };
			// Not owning container
			std::deque<IObserver*> m_observers;
	};

} // GE
