#include"pch.h"

#include"ToadApplication.h"

namespace Toad
{
	void ToadApplication::Initialize()
	{

	}

	void ToadApplication::OnUpdate()
	{
	}

	void ToadApplication::Shutdown()
	{

	}

	void ToadApplication::Run()
	{
		Initialize();

		while (true)
		{
			OnUpdate();

		}

		Shutdown();

	}

}