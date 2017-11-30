#include "Actor.hpp"

namespace vn
{
	const std::string & Actor::GetActorID()
	{
		return m_ActorID;
	}
	const std::string & Actor::GetActorName()
	{
		return m_Name;
	}
	const std::string & Actor::GetActorExpression()
	{
		return m_Expression;
	}
	int Actor::GetPosition()
	{
		return m_Position;
	}
}
