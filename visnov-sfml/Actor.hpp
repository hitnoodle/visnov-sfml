#pragma once

#include "Block.hpp"
#include <string>

namespace vn
{
	class Actor : public Block
	{
	private:
		std::string m_ActorID;
		std::string m_Name;
		std::string m_Expression;
		int m_Position; // Index of it's position
	public:
		Actor() : Block("Actor", "a"), m_ActorID(""), m_Position(0) {};
		Actor(const std::string& actorID, const std::string& name, const std::string& expression, int position) : Block("Actor", "a"), m_ActorID(actorID), m_Name(name), m_Expression(expression), m_Position(position) {};
	
		const std::string& GetActorID();
		const std::string& GetActorName();
		const std::string& GetActorExpression();
		int GetPosition();
	};
}