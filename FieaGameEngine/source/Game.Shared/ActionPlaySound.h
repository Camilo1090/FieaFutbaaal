#pragma once

#include "Action.h"
#include "bass.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class ActionPlaySound :
		public Action
	{
		RTTI_DECLARATIONS(ActionPlaySound, Action)

	public:
		static const std::string FilePath;
		static const std::string IsSoundEffect;
		static Vector<Signature> Signatures();

	public:
		explicit ActionPlaySound(const std::string& name = std::string());
		virtual ~ActionPlaySound() = default;

		virtual gsl::owner<ActionPlaySound*> Clone() const override;
		virtual void Update(WorldState& worldState);

	private:

		std::string mFilePath;
		int mIsSoundEffect;
		HSAMPLE* mSample;
	};

	CONCRETE_FACTORY(ActionPlaySound, Scope)
}