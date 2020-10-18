#include "core/IObservable.h"

namespace GE
{

	bool IObservable::addObserver(IObserver * observer)
	{
		// Check if collection contains the observer.
		if (std::find(std::begin(m_observers), std::end(m_observers), observer) == m_observers.end())
		{
			m_observers.push_back(observer);
			++m_observersCount;

			return true;
		}

		return false;
	}

	bool IObservable::removeObserver(IObserver * observer)
	{
		auto deletedCount = std::erase_if(m_observers,
			[&observer](IObserver * obs)
			{
				return obs == observer;
			});

		if (deletedCount)
		{
			--m_observersCount;

			return true;
		}

		return false;
	}

	void IObservable::notifyObservers() const
	{
		std::for_each(std::begin(m_observers), std::end(m_observers),
			[this](IObserver * observer) { observer->updateEvent(this); } );
	}

	bool IObservable::hasObservers() const
	{
		return m_observersCount > 0;
	}

	size_t IObservable::getObserversCount() const
	{
		return m_observersCount;
	}

} // GE
