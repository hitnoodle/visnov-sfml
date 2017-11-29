#include "Block.hpp"

namespace vn
{
	Block::Block()
	{
		m_ID = "Unassigned";
		m_Command = "none";
		m_IsFinished = false;
	}

	Block::Block(std::string id, std::string command)
	{
		m_ID = id;
		m_Command = command;
		m_IsFinished = false;
	}

	const std::string& Block::GetID()
	{
		return m_ID;
	}

	const std::string& Block::GetCommand()
	{
		return m_Command;
	}
}