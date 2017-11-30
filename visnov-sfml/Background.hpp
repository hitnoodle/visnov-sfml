#pragma once

#include "Block.hpp"
#include <string>

namespace vn
{
	class Background : public Block
	{
	private:
		std::string m_BackgroundID;
	public:
		Background() : Block("Background", "bg"), m_BackgroundID("") {};
		Background(const std::string& backgroundID) : Block("Background", "bg"), m_BackgroundID(backgroundID) {};

		const std::string& GetBackgroundID();
	};
}