#include <iostream>
#include <gtest/gtest.h>

#include "core/IObserver.h"
#include "core/IObservable.h"

class ObservableItem : public GE::IObservable
{
	public:
		ObservableItem() = default;

		// Actions
		void triggerEvent()
		{
			m_value = 10;
			GE::IObservable::notifyObservers();
		}

		uint getValue() const
		{
			return m_value;
		}

	private:
		uint m_value = { 0 };
};

class ObservingEntity : public GE::IObserver
{
	public:
		ObservingEntity() = default;

		// Override updateEvent from IObservable class
		void updateEvent(const GE::IObservable * observable) override
		{
			auto obs = dynamic_cast<const ObservableItem*>(observable);

			// Check if the ptr is valid
			if (obs) [[likely]]
				m_value = obs->getValue();
			else
				// Test failed
				ASSERT_TRUE(false);
		}

		uint getValue() const
		{
			return m_value;
		}

	private:
		uint m_value { 3 };
};

TEST(ObservableImplementationTest, NotifyEventTest)
{
	ObservingEntity observingEntity;

	ObservableItem observableItem;
	ASSERT_TRUE(observableItem.addObserver(&observingEntity));

	ASSERT_EQ(observableItem.getValue(), 0);
	ASSERT_EQ(observingEntity.getValue(), 3);

	// Create event
	observableItem.triggerEvent();

	ASSERT_EQ(observableItem.getValue(), 10);
	ASSERT_EQ(observingEntity.getValue(), 10);
}

TEST(ObservableImplementationTest, ObserversCountTest)
{
	ObservingEntity observingEntity1;

	ObservableItem observableItem;
	ASSERT_EQ(observableItem.hasObservers(), false);
	ASSERT_EQ(observableItem.getObserversCount(), 0);

	ASSERT_TRUE(observableItem.addObserver(&observingEntity1));
	ASSERT_EQ(observableItem.hasObservers(), true);
	ASSERT_EQ(observableItem.getObserversCount(), 1);

	ObservingEntity observingEntity2;
	ASSERT_TRUE(observableItem.addObserver(&observingEntity2));
	ASSERT_EQ(observableItem.getObserversCount(), 2);

	ASSERT_TRUE(observableItem.removeObserver(&observingEntity2));
	ASSERT_EQ(observableItem.getObserversCount(), 1);

	ASSERT_TRUE(observableItem.removeObserver(&observingEntity1));
	ASSERT_EQ(observableItem.getObserversCount(), 0);
}

TEST(ObservableImplementationTest, RepeatedAdding)
{
	ObservingEntity observingEntity1;

	ObservableItem observableItem;
	ASSERT_TRUE(observableItem.addObserver(&observingEntity1));
	ASSERT_FALSE(observableItem.addObserver(&observingEntity1));
}

TEST(ObservableImplementationTest, ReapeatedDeleting)
{
	ObservingEntity observingEntity1;

	ObservableItem observableItem;
	ASSERT_TRUE(observableItem.addObserver(&observingEntity1));

	ASSERT_TRUE(observableItem.removeObserver(&observingEntity1));
	ASSERT_FALSE(observableItem.removeObserver(&observingEntity1));
}

TEST(ObservableImplementationTest, hasObserversTest)
{
	ObservingEntity observingEntity1;

	ObservableItem observableItem;
	ASSERT_FALSE(observableItem.hasObservers());

	ASSERT_TRUE(observableItem.addObserver(&observingEntity1));
	ASSERT_TRUE(observableItem.hasObservers());
}

int main(int argc, char ** argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
