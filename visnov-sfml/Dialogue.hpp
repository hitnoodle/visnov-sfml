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
		Dialogue(const std::string& line) : Block("Dialogue", "d"), m_Line(line) {};

		void setLine(const std::string& line);
		const std::string& GetLine();
	};
}