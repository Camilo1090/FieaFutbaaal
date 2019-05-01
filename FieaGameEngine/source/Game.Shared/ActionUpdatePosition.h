#pragma once

#include "Action.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class ActionUpdatePosition : public Action
	{
		RTTI_DECLARATIONS(ActionUpdatePosition, Action)

	public:
		static Vector<Signature> Signatures();

	public:
		explicit ActionUpdatePosition(const std::string& name = std::string());
		virtual ~ActionUpdatePosition() = default;

		virtual gsl::owner<ActionUpdatePosition*> Clone() const override;
		virtual void Update(WorldState& worldState) override;

	};

	CONCRETE_FACTORY(ActionUpdatePosition, Scope)
}
