#include "graphics/RenderProperties.h"

namespace GE
{

	uMap<sview, propValue> RenderProperties::m_properties
	{
		{ "FIELD_OF_VIEW", 70.f },
		{ "NEAR_PLANE",    0.1f },
		{ "FAR_PLANE",     1000.f }
	};

	void RenderProperties::updateProperty(const sview propertyName,
	                                      const propValue & value)
	{
		m_properties[propertyName] = value;
	}

	propValue RenderProperties::getProperty(const sview propertyName)
	{
		// Can throw out_of_range exception in case when value is not found.
		return m_properties.at(propertyName);
	}

} // GE
