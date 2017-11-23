#pragma once

#include "Block.hpp"
#include <string>

namespace vn
{
	class Dialogue : public Block
	{
	private:
		std::string m_Line;
	public:
		Dialogue() : Block("Dialogue", "d"), m_Line("") {};
		Dialogue(std::string line) : Block("Dialogue", "d"), m_Line(line) {};

		void setLine(std::string line);
		std::string GetLine();
	};
}