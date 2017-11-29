#pragma once

#include <string>

namespace vn
{
	class Block
	{
	protected:
		std::string m_ID;
		std::string m_Command;
		bool m_IsFinished;
	public:
		Block();
		Block(std::string id, std::string command);

		const std::string& GetID();
		const std::string& GetCommand();
	};
}