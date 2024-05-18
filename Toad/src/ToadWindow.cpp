#include"pch.h"
#include"ToadWindow.h"
#include"codeGLFW/WindowGLFW.h"

namespace Toad
{
	ToadWindow::ToadWindow()
	{
#ifdef TOAD_GLFW_WINDOW
		mWindow = std::unique_ptr<WindowImpl>{ new WindowGLFW };
#else
	#definition_TOAD_GLFW_is_missing
#endif
	}


	void ToadWindow::Init()
	{
		if (!mInstance)
			mInstance = new ToadWindow;
	}

	ToadWindow* ToadWindow::GetWindow()
	{
		return mInstance;
	}

	void ToadWindow::Shutdown()
	{
		if (mInstance)
			delete mInstance;
	}

	void ToadWindow::SwapBuffers()
	{
		mWindow->SwapBuffers();
	}

	void ToadWindow::PollEvents()
	{
		mWindow->PollEvents();
	}

	void ToadWindow::Create(int width, int height)
	{
		mWindow->Create(width, height);
	}

	int ToadWindow::GetWidth() const
	{
		return mWindow->GetWidth();
	}

	int ToadWindow::GetHeight() const
	{
		return mWindow->GetHeight();
	}

}