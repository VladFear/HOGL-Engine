#include <gtest/gtest.h>

#include "core/UnownedPtr.h"

using namespace GE;

TEST(UnownedPtrTest, CreationTestNull)
{
	UnownedPtr<int> ptr;
	ASSERT_EQ(ptr, nullptr);
}

TEST(UnownedPtrTest, CreationTestNotNull)
{
	UnownedPtr ptr(new int);
	ASSERT_NE(ptr, nullptr);
}

TEST(UnownedPtrTest, ConvertionToBoolNull)
{
	UnownedPtr<int> ptr;
	ASSERT_FALSE(ptr);
}

TEST(UnownedPtrTest, ConvertionToBoolNotNull)
{
	UnownedPtr<int> ptr(new int);
	ASSERT_TRUE(ptr);
}

TEST(UnownedPtrTest, Equality)
{
	int * raw = new int;
	*raw = 15;

	UnownedPtr ptr(raw);

	int * raw2 = new int;
	*raw2 = 3;
	UnownedPtr another(raw2);

	ASSERT_NE(ptr, another);

	another.reset(raw);
	ASSERT_EQ(ptr, another);

	delete raw;
	delete raw2;
}

TEST(UnownedPtrTest, ResetFunc)
{
	UnownedPtr<int> ptr;
	ASSERT_FALSE(ptr);

	int * raw = new int;
	*raw = 15;

	ptr.reset(raw);
	ASSERT_TRUE(ptr);

	delete raw;
	raw = nullptr;

	ptr.reset(raw);
	ASSERT_FALSE(ptr);
}

TEST(UnownedPtrTest, GetFunc)
{
	int * raw = new int;
	*raw = 15;

	UnownedPtr ptr(raw);
	ASSERT_EQ(raw, ptr.get());

	delete raw;
}

TEST(UnownedPtrTest, ReleaseFunc)
{
	int * raw = new int;
	*raw = 15;

	UnownedPtr ptr(raw);
	ASSERT_EQ(*raw, *ptr);

	int * another_raw = ptr.release();
	ASSERT_EQ(*raw, *another_raw);

	ASSERT_FALSE(ptr);

	delete raw;
}

TEST(UnownedPtrTest, StarOperator)
{
	int * raw = new int;
	*raw = 15;

	UnownedPtr ptr(raw);
	ASSERT_EQ(*raw, *ptr);

	delete raw;
}

TEST(UnownedPtrTest, MoveSemantics)
{
	int * raw = new int;
	*raw = 15;

	UnownedPtr ptr(raw);
	ASSERT_TRUE(ptr);

	UnownedPtr another(std::move(ptr));
	ASSERT_TRUE(another);
	ASSERT_FALSE(ptr);

	ptr = std::move(another);
	ASSERT_TRUE(ptr);
	ASSERT_FALSE(another);

	delete raw;
}

TEST(UnownedPtrTest, CopySemantics)
{
	int * raw = new int;
	*raw = 15;

	UnownedPtr ptr(raw);
	ASSERT_TRUE(ptr);

	UnownedPtr another(ptr);

	ASSERT_EQ(*raw, *ptr);
	ASSERT_EQ(*raw, *another);

	UnownedPtr secondAnother = another;;
	ASSERT_EQ(*secondAnother, *another);

	delete raw;
}

TEST(UnownedPtrTest, ValueModification)
{
	int * raw = new int;
	*raw = 15;

	UnownedPtr ptr(raw);
	ASSERT_EQ(*ptr, 15);

	*raw = 3;
	ASSERT_EQ(*ptr, 3);

	delete raw;
}

TEST(UnownedPtrTest, CallFunctions)
{
	struct TestStruct
	{
		int sum(int a , int b)
		{
			return a + b;
		}
	};

	TestStruct * s = new TestStruct;
	UnownedPtr ptr(s);

	ASSERT_EQ(ptr->sum(1, 2), 3);

	delete s;
}

int main(int argc, char ** argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
