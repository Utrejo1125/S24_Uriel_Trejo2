#pragma once
#include"pch.h"

#include"Utility.h"
#include"ImageImplement.h"

namespace Toad
{
	class TOAD_API Image
	{
	public:
		Image(const std::string& filePath);
		Image(std::string&& filePath);

		int GetWidth() const;
		int GetHeight() const;

		void Bind();


	private:
		std::unique_ptr<ImageImplement> mImplementation;
	};
}