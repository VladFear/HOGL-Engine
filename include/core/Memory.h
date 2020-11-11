#pragma once

#include <memory>

#include "core/UnownedPtr.h"

namespace GE
{

	template <typename T>
	using Unique = std::unique_ptr<T>;

	template <typename T>
	using Shared = std::shared_ptr<T>;

	template <typename T, typename... ArgsTypes>
	constexpr Unique<T> createUnique(ArgsTypes && ... args)
	{
		return std::make_unique<T>(std::forward<ArgsTypes>(args)...);
	}

	template <typename T, typename... ArgsTypes>
	constexpr Shared<T> createShared(ArgsTypes && ... args)
	{
		return std::make_shared<T>(std::forward<ArgsTypes>(args)...);
	}

}
