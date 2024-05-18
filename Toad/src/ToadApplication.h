#pragma once

#include "Utility.h"

namespace Toad
{
	class TOAD_API ToadApplication
	{
	public:
		virtual void Initialize();
		virtual void OnUpdate();
		virtual void Shutdown();

		void Run();

	private:

	};
}