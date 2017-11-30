#include "Dialogue.hpp"

namespace vn
{
	void Dialogue::setLine(const std::string& line)
	{
		m_Line = line;
	}

	const std::string& Dialogue::GetLine()
	{
		return m_Line;
	}
}
