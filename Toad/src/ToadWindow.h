#pragma once

#include"pch.h"
#include"WindowImpl.h"
#include"Utility.h"

namespace Toad
{
	class TOAD_API ToadWindow
	{
	public:
		static void Init();
		static ToadWindow* GetWindow();
		static void Shutdown();

		void SwapBuffers();
		void PollEvents();
		void Create(int width, int height);
		int GetWidth() const;
		int GetHeight() const;

	private:
		inline static ToadWindow* mInstance{ nullptr };

		std::unique_ptr <WindowImpl> mWindow{ nullptr };

		ToadWindow();
	};

}