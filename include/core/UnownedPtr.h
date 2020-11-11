#pragma once

namespace GE
{

	template <typename T>
	class UnownedPtr final
	{
		public:
			UnownedPtr() = default;
			explicit UnownedPtr(T * ptr) : m_ptr { ptr }
			{ }

			UnownedPtr(const UnownedPtr &)             = default;
			UnownedPtr & operator=(const UnownedPtr &) = default;

			UnownedPtr(UnownedPtr && other)
			{
				if (&other != this)
				{
					m_ptr = other.m_ptr;
					other.m_ptr = nullptr;
				}
			}

			UnownedPtr & operator=(UnownedPtr && other)
			{
				if (&other != this)
				{
					m_ptr = other.m_ptr;
					other.m_ptr = nullptr;
				}

				return *this;
			}

			constexpr T * operator->() const noexcept
			{
				return m_ptr;
			}

			constexpr T& operator*() const noexcept
			{
				return *m_ptr;
			}

			constexpr T * get() const noexcept
			{
				return m_ptr;
			}

			constexpr T * release() noexcept
			{
				return std::exchange(m_ptr, nullptr);
			}

			constexpr void reset(T * const raw) noexcept
			{
				m_ptr = raw;
			}

			explicit constexpr operator bool() const noexcept
			{
				return m_ptr ? true : false;
			}

			constexpr bool operator==(const UnownedPtr & other) const noexcept
			{
				return m_ptr == other.get();
			}

			constexpr bool operator!=(const UnownedPtr & other) const noexcept
			{
				return m_ptr != other.get();
			}

			constexpr bool operator==(T * const raw) const noexcept
			{
				return m_ptr == raw;
			}

			constexpr bool operator!=(T * const raw) const noexcept
			{
				return m_ptr != raw;
			}

		private:
			T * m_ptr = nullptr;
	};

}
