#pragma once

#include "pch.h"
#include "Utility.h"
#include "ToadEvents.h"

constexpr int TOAD_FRAME_RATE{ 60 };

namespace Toad
{
	class TOAD_API ToadApplication
	{
	public:
		ToadApplication();

		virtual void Initialize();
		virtual void OnUpdate();
		virtual void Shutdown();

		void Run();

		void SetKeyPressedCallback(std::function<void(const KeyPressed&)> callbackFunc);
		void SetKeyReleasedCallback(std::function<void(const KeyReleased&)> callbackFunc);
		void SetWindowCloseCallback(std::function<void()> callbackFunc);

		void DefaultWindowCloseHandler();

	private:
		std::chrono::steady_clock::time_point mNextFrameTime;
		std::chrono::duration<int, std::chrono::milliseconds::period> mFrameDuration{ 1000 / TOAD_FRAME_RATE };

		bool mShouldContinue{ true };
	};
}