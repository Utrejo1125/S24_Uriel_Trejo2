#pragma once

#include "Utility.h"

namespace Toad
{
	class TOAD_API KeyPressed
	{
	public:
		KeyPressed(int kCode);

		int GetKeyCode() const;

	private:	
		int mKeyCode;
	};

	class TOAD_API KeyReleased
	{
	public:
		KeyReleased(int kCode);

		int GetKeyCode() const;

	private:
		int mKeyCode;
	};
}
