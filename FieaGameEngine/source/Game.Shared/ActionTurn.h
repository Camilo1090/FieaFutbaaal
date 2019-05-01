#pragma once

#include "Action.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class ActionTurn : public Action
	{
		RTTI_DECLARATIONS(ActionTurn, Action)

	public:
		static const std::string TargetKey;
		static const std::size_t TargetIndex;
		static const std::string TargetRotationKey;
		static const std::size_t TargetRotationIndex;
		static const std::string RotationRateKey;
		static const std::size_t RotationRateIndex;
		static Vector<Signature> Signatures();

	public:
		
		explicit ActionTurn();
		virtual ~ActionTurn() = default;

		virtual gsl::owner<ActionTurn*> Clone() const override;

		virtual void Update(WorldState& worldState) override;

		bool ClockwiseRotationIsShortest(float currentRotation) const;
		bool TargetRotationWithinRotationAmount(float currentRotation) const;

	private:
		/// <summary>
		/// 
		/// </summary>
		std::string mTarget;

		/// <summary>
		/// 
		/// </summary>
		float mTargetRotation = 0;

		/// <summary>
		/// 
		/// </summary>
		float mRotationRate = 0;

		/// <summary>
		/// 
		/// </summary>
		float mRotationThisTick = 0;
		
	};

	CONCRETE_FACTORY(ActionTurn, FieaGameEngine::Scope)
}