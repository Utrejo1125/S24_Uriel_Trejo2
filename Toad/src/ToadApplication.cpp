#include"pch.h"

#include"ToadApplication.h"
#include"ToadWindow.h"
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include"stb_image.h"

#include"Renderer.h"
#include"Image.h"
#include"Shader.h"
#include"ToadKeys.h"

namespace Toad
{
	ToadApplication::ToadApplication()
	{
		ToadWindow::Init();
		ToadWindow::GetWindow()->Create(1000, 800);

		Renderer::Init();

		SetWindowCloseCallback([this]() {DefaultWindowCloseHandler();  });
	}

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

		mNextFrameTime = std::chrono::steady_clock::now() + mFrameDuration;

		while (mShouldContinue)
		{
			Renderer::ClearScreen();

			OnUpdate();

			std::this_thread::sleep_until(mNextFrameTime);
			mNextFrameTime = std::chrono::steady_clock::now() + mFrameDuration;

			ToadWindow::GetWindow()->SwapBuffers();
			ToadWindow::GetWindow()->PollEvents();
		}

		Shutdown();

		ToadWindow::Shutdown();
	}


	void ToadApplication::SetKeyPressedCallback(std::function<void(const KeyPressed&)> callbackFunc)
	{
		ToadWindow::GetWindow()->SetKeyPressedCallback(callbackFunc);
	}	
	

	void ToadApplication::SetKeyReleasedCallback(std::function<void(const KeyReleased&)> callbackFunc)
	{
		ToadWindow::GetWindow()->SetKeyReleasedCallback(callbackFunc);
	}	
	

	void ToadApplication::SetWindowCloseCallback(std::function<void()> callbackFunc)
	{
		ToadWindow::GetWindow()->SetWindowCloseCallback(callbackFunc);
	}

	void ToadApplication::DefaultWindowCloseHandler()
	{
		mShouldContinue = false;
	}

}