#pragma once

#include"Utility.h"
#include"Image.h"

namespace Toad
{
	class TOAD_API Unit
	{
	public:
		Unit(const std::string& image, int x, int y);
		Unit(std::string&& image, int x, int y);

		int GetWidth() const;
		int GetHeight() const;

		int GetXCord() const;
		int GetYCord() const;
		void SetCoords(int x, int y);
		void UpdateXCoord(int amount);
		void UpdateYCoord(int amount);

	private:
		Image mImage;
		int mXPosition;
		int mYPosition;

		friend TOAD_API bool UnitsOverlap(const Unit& a, const Unit& b);
		friend class Renderer; 
	};

	TOAD_API bool UnitsOverlap(const Unit& a, const Unit& b);
}