#include "pch.h"
#include "ReactionScore.h"
#include "Event.h"

namespace FieaGameEngine
{
	ReactionScore::ReactionScore() : Reaction(ReactionScore::TypeIdClass())
	{
		Event<std::pair<bool,int>>::Subscribe(*this);
	}


	ReactionScore::~ReactionScore()
	{
	}
}