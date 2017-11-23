#include "Dialogue.hpp"

namespace vn
{
	void Dialogue::setLine(std::string line)
	{
		m_Line = line;
	}

	std::string Dialogue::GetLine()
	{
		return m_Line;
	}
}
