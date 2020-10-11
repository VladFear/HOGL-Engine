#pragma once

#include <unordered_map>
#include <string_view>
#include <variant>

namespace GE
{

	template <typename K, typename V>
	using uMap = std::unordered_map<K, V>;

	using sview = std::string_view;
	using propValue = std::variant<int, float>;

	class RenderProperties
	{
		public:
			// Actions
			static void updateProperty(const sview propertyName,
			                           const propValue & value);
			static propValue getProperty(const sview propertyName);

		private:
			static uMap<sview, propValue> m_properties;
	};

} // GE
