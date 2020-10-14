#pragma once

namespace GE
{

	class IBufferObject
	{
		public:
			virtual ~IBufferObject() = default;

			// Actions
			virtual void bind() const = 0;
			virtual void unbind() const = 0;
	};

} // Ge
