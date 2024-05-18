#include"pch.h"

#include"ToadApplication.h"
#include"ToadWindow.h"

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
		ToadWindow::Init();
		ToadWindow::GetWindow()->Create(1000, 800);

		Initialize();

		while (true)
		{
			OnUpdate();

			ToadWindow::GetWindow()->SwapBuffers();
			ToadWindow::GetWindow()->PollEvents();
		}

		Shutdown();

		ToadWindow::Shutdown();
	}

}