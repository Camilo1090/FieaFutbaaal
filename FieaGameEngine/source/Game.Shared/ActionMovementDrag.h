#pragma once

#include "Action.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class ActionMovementDrag : public Action
	{
		RTTI_DECLARATIONS(ActionMovementDrag, Action)

	public:
		static const std::string DragKey;
		static Vector<Signature> Signatures();

	public:
		explicit ActionMovementDrag(float drag = 1.0f, const std::string& name = std::string());
		virtual ~ActionMovementDrag() = default;

		virtual gsl::owner<ActionMovementDrag*> Clone() const override;
		virtual void Update(WorldState& worldState) override;

		float& Drag();
		const float& Drag() const;

	private:
		float mDrag;
	};

	CONCRETE_FACTORY(ActionMovementDrag, Scope)
}
